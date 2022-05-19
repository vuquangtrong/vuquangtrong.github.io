#!/usr/bin/env python3

import socket
import datetime
import http.server

class ExampleHTTPHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/time':
            self.send_response(200)
            self.send_header('Content-Type', 'text/plain')
            self.end_headers()
            # get current time
            now = datetime.datetime.now().strftime("%H:%M:%S")
            self.wfile.write(now.encode())
            self.wfile.write(b'\r\n')
        else:
            # fallback to default handler
            super().do_GET()

def main():
    print("IP Addresses:")
    for i in socket.getaddrinfo(socket.gethostname(), None):
        print(i[4][0])

    # Run webserver on localhost:80
    server_address = ('', 80)
    # using multithread and ExampleHTTPHandler
    httpd = http.server.ThreadingHTTPServer(server_address, ExampleHTTPHandler)
    print("Server starts")
    httpd.serve_forever()

if __name__ == "__main__":
    main()
