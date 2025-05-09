const WS_URL = 'wss://192.168.31.176:12345/';
const ws = new WebSocket(WS_URL);
//const wsState = document.getElementById('wsState');

//ws.addEventListener('open', () => { wsState.textContent = 'Подключено'; });
//ws.addEventListener('close', () => { wsState.textContent = 'Отключено'; });
//ws.addEventListener('error', () => { wsState.textContent = 'Ошибка'; });

let tilt = { x: 0, y: 0, z: 0 };
let pedals = { gas: 0, brake: 0, clutch: 0 };

// Обновление отображения значений
function updateDisplay(id, val) {
    document.getElementById('val' + id.charAt(0).toUpperCase() + id.slice(1))
        .textContent = val.toFixed(2);
}

['gas', 'brake', 'clutch'].forEach(id => {
    const el = document.getElementById(id);
    el.addEventListener('input', () => {
        pedals[id] = parseFloat(el.value);
        updateDisplay(id, pedals[id]);
    });
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
                    alert('Доступ к датчикам отклонён');
                }
            })
            .catch(err => console.error(err));
    }
});

setInterval(() => {
    if (ws.readyState !== WebSocket.OPEN) return;
    const msg = { type: 'sensor_update', tilt, pedals, timestamp: Date.now() };
    ws.send(JSON.stringify(msg));
}, 50);