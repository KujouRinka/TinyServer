### TinyServer

A demo server, for understanding how a web server is running.

##### Running with docker

`docker build -t tiny-server .`

`docker run -d -p 80:80 --name tiny-server-container tiny-server`

ps: `main.go` 使用 golang 实现，一个源文件全部实现
