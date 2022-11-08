const symbols = [
    ['1', '2', '3', 'A'],
    ['4', '5', '6', 'B'],
    ['7', '8', '9', 'C'],
    ['*', '0', '#', 'D']
];

let led_state = new Array(8);
for (let i = 0; i < led_state.length; i++) {
    led_state[i] = new Array(8);
    for (let j = 0; j < led_state[i].length; j++)
        led_state[i][j] = false;
}

function draw_keyboard(ctx_kbd)
{
    for (let row=0; row<4; ++row)
        for (let col=0; col<4; ++col)
        {
            ctx_kbd.fillStyle = "black";
            ctx_kbd.fillRect(col*50,row*50, 50, 50);
            ctx_kbd.strokeStyle = "white";
            ctx_kbd.strokeRect(col*50,row*50, 50, 50)
            ctx_kbd.fillStyle = "white";
            ctx_kbd.font = '36px serif';
            ctx_kbd.fillText(symbols[row][col],col*50+15,row*50+35)
        }
}

function draw_matrix(ctx_mtr)
{
    ctx_mtr.fillStyle = "black";
    ctx_mtr.fillRect(0,0, 200, 200);
    for (let row=0; row<8; ++row)
        for (let col=0; col<8; ++col)
        {
            if (led_state[row][col])
                ctx_mtr.fillStyle = "#FF0000";
            else
                ctx_mtr.fillStyle = "#BBBBBB";
            ctx_mtr.beginPath();
            ctx_mtr.arc(12+25*row, 12+25*col, 10, 0, 2 * Math.PI);
            ctx_mtr.fill();
        }
}

function find_symbol(symbol)
{
    for (let row=0; row<4; ++row)
        for (let col=0; col<4; ++col)
            if (symbols[row][col] == symbol)
            {
                let result = {r:row, c:col};
                return result;
            }
}

function blink(ctx, symbol)
{
    ctx.fillStyle = "white";
    res = find_symbol(symbol);
    ctx.fillRect(res.c*50, res.r*50, 50, 50);
    setInterval(function() { draw_keyboard(ctx); }, 1000);
}

document.addEventListener('DOMContentLoaded', function()
{
    const log_div = document.getElementById("data");
    log_div.innerText = "Ready to go!";

    const canvas_keyboard = document.getElementById("keyboard");
    const ctx_kbd = canvas_keyboard.getContext("2d");

    const canvas_matrix = document.getElementById("matrix");
    const ctx_mtr = canvas_matrix.getContext("2d");

    let socket = new WebSocket("ws://localhost:2022");

    canvas_matrix.addEventListener('click', function(event)
    {
        let rect = event.target.getBoundingClientRect();
        let x = event.x - rect.left;
        let y = event.y - rect.top;
        let row = Math.floor(x/25);
        let col = Math.floor(y/25);
        led_state[row][col] = !led_state[row][col];
        let str = "";
        str += row;
        str += col;
        str += 1*led_state[row][col];
        str += '\n';
        log_div.innerText = str;
        socket.send(str);
        // log_div.innerText = `click! ${row} ${col}`;
        draw_matrix(ctx_mtr);
    });

    socket.onopen = function(e) {
        console.log("[open] Connected");
    };

    socket.onmessage = function(event) {
        str = event.data.trim();
        console.log(`[message] Received: ${str}`);
        blink(ctx_kbd, str);
    };

    socket.onclose = function(event) {
        if (event.wasClean)
            console.log(`[close] Closed connection, code=${event.code} reason=${event.reason}`);
        else
            console.log('[close] Connection aborted');
    };

    socket.onerror = function(error) {
        console.log(`[error] ${error.message}`);
    };

    draw_keyboard(ctx_kbd);
    draw_matrix(ctx_mtr);
});