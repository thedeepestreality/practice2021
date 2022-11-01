console.log("Hello world!");

const symbols = [
    ['1', '2', '3', 'A'],
    ['4', '5', '6', 'B'],
    ['7', '8', '9', 'C'],
    ['*', '0', '#', 'D']
];

document.addEventListener('DOMContentLoaded', function(){
    var divElem = document.getElementById("data");
    divElem.innerText = "new text";

    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");

    let socket = new WebSocket("ws://localhost:2022");

    socket.onopen = function(e) {
        console.log("[open] Connected");
        console.log("Sending data");
        //socket.send("My name is John");
    };

    socket.onmessage = function(event) {
        str = event.data.trim()
        console.log(`[message] Received: ${str}`);
        if (str == "3")
        {
            blink();
        }
        
    };

    function blink()
    {
        ctx.fillStyle = "white";
        ctx.fillRect(0, 0, 50, 50);
        loop = setInterval(draw, 1000);
    }

    socket.onclose = function(event) {
    if (event.wasClean) {
        console.log(`[close] Closed connection, code=${event.code} reason=${event.reason}`);
    } else {
        // например, сервер убил процесс или сеть недоступна
        // обычно в этом случае event.code 1006
        console.log('[close] Connection aborted');
    }
    };

    socket.onerror = function(error) {
        console.log(`[error] ${error.message}`);
    };

    
    
    draw();

    

    function draw()
    {
        for (let row=0; row<4; ++row)
            for (let col=0; col<4; ++col)
            {
                ctx.fillStyle = "black";
                ctx.fillRect(col*50,row*50, 50, 50);
                ctx.strokeStyle = "white";
                ctx.strokeRect(col*50,row*50, 50, 50)
                ctx.fillStyle = "white";
                ctx.font = '36px serif';
                ctx.fillText(symbols[row][col],col*50+15,row*50+35)
            }
    }
});