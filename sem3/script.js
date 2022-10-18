console.log("Hello world!");

document.addEventListener('DOMContentLoaded', function(){
    var divElem = document.getElementById("data");
    divElem.innerText = "new text";

    let socket = new WebSocket("ws://localhost:2022");

    socket.onopen = function(e) {
        console.log("[open] Connected");
        console.log("Sending data");
        socket.send("My name is John");
    };

    socket.onmessage = function(event) {
        console.log(`[message] Received: ${event.data}`);
    };

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
});