import socketserver

class TCPHandler(socketserver.StreamRequestHandler):
    users = ["ChuckNorris", "me", "you"]
    def handle(self):
        # self.rfile is a file-like object created by the handler;
        # we can now use e.g. readline() instead of raw recv() calls

        # # # # muli-line request:
        # # # for data in self.rfile:
        # # #     print(data)
        # # # self.data_raw = self.rfile.readlines()

        self.data = self.rfile.readline().strip()

        # split url into path and vars
        url = self.data.decode('UTF-8').split()[1]
        url_split = url.split("?")
        path = url_split[0]
        vars_array = []
        if (len(url_split) > 1):
            vars_array = url_split[1].split("&")
        vars = {}
        for var in vars_array:
            pair = var.split("=")
            vars[pair[0]] = pair[1]
        print(path)
        print(vars)

        # build response
        response = ""
        if (path == "/"):
            response += "HTTP/1.1 200 OK\n"
            response += "Content-Type: text/html; charset=utf-8\n\n"
            response += "<b>SUCCESS</b>"
        elif (path == "/admin"):
            response += "HTTP/1.1 200 OK\n"
            response += "Content-Type: text/html; charset=utf-8\n\n"
            response += "<b>HELLO ADMIN</b>"
        elif (path == "/users"):
            id = int(vars["id"])
            user = self.users[id]
            response += "HTTP/1.1 200 OK\n"
            response += "Content-Type: text/html; charset=utf-8\n\n"
            response += f"<b>FOUND USER: {user}</b>"
        else:
            response += "HTTP/1.1 404 NOT FOUND\n"
        self.wfile.write(response.encode())

if __name__ == "__main__":
    with socketserver.TCPServer(("localhost", 80), TCPHandler) as server:
        server.serve_forever()
