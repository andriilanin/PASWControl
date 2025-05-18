let hostIP;
let ws;
fetch('/hostIP')
    .then(res => res.json())
    .then(data => {
        hostIP = data.hostIP;
        const WS_URL = `wss://${hostIP}:12345/`;
        ws = new WebSocket(WS_URL);
        ws.addEventListener('close', () => {
            document.querySelectorAll('.custom-slider').forEach(slider => {
                slider.classList.toggle("disconnected");
            });
        });
    })
    .catch(err => console.error('error receiving hostIP:', err));

let tilt = { x: 0, y: 0, z: 0 };
let pedals = { gas: 0, brake: 0, clutch: 0 };
let pressedButton = "";

function setupSlider(sliderElem, id) {
    const thumb = sliderElem.querySelector('.thumb');
    const width = sliderElem.clientWidth;

    function setValueFromX(x) {
        const rect = sliderElem.getBoundingClientRect();
        let relativeX = x - rect.left-60;
        relativeX = Math.max(0, Math.min(relativeX, width-70));
        const rawValue = relativeX / width;
        const value255 = Math.round(rawValue * 340);
        pedals[id] = value255;
        thumb.style.left = `${rawValue * 100}%`;
    }

    sliderElem.addEventListener('pointerdown', e => {
        e.preventDefault();
        sliderElem.setPointerCapture(e.pointerId);
        setValueFromX(e.clientX);
    });

    sliderElem.addEventListener('pointermove', e => {
        if (e.buttons) {
            setValueFromX(e.clientX);
        }
    });
}

document.querySelectorAll('.custom-slider').forEach(slider => {
    const id = slider.getAttribute('id');
    setupSlider(slider, id);
});

document.getElementById('btn1').addEventListener('pointerdown', () => {
    pressedButton = "btn1";
    //setTimeout(() => {
    //    pressedButton = "";
    //}, 250);
});

document.getElementById('btn2').addEventListener('pointerdown', () => {
    pressedButton = "btn2";
    //setTimeout(() => {
    //    pressedButton = "";
    //}, 250);
});

document.getElementById('btn3').addEventListener('pointerdown', () => {
    pressedButton = "btn3";
    //setTimeout(() => {
    //    pressedButton = "";
    //}, 250);
});

document.getElementById('btn4').addEventListener('pointerdown', () => {
    pressedButton = "btn4";
    //setTimeout(() => {
    //    pressedButton = "";
    //}, 250);
});

document.getElementById('btnPerms').addEventListener('click', () => {
    if (DeviceOrientationEvent.requestPermission) {
        DeviceOrientationEvent.requestPermission()
            .then(resp => {
                if (resp === 'granted') {
                    permsButton = document.querySelector("#btnPerms");
                    permsButton.classList.toggle("hide")
                    window.addEventListener('devicemotion', ev => {
                        tilt.x = ev.accelerationIncludingGravity.x ? (ev.accelerationIncludingGravity.x) : 0;
                        tilt.y = ev.accelerationIncludingGravity.y ? (ev.accelerationIncludingGravity.y) : 0;
                        tilt.z = ev.accelerationIncludingGravity.z ? (ev.accelerationIncludingGravity.z) : 0;
                    });
                } else {
                    alert('sensors permission denied');
                }
            })
            .catch(err => console.error(err));
    }
});

setInterval(() => {
    if (ws.readyState !== WebSocket.OPEN) return;
    const msg = { type: 'sensor_update', tilt, pedals, pressedButton, timestamp: Date.now() };
    ws.send(JSON.stringify(msg));
    pressedButton = "";
}, 25);