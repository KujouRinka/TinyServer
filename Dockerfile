FROM ubuntu:latest
RUN apt-get update && apt-get install -y g++ make cmake
COPY . /usr/src/app
WORKDIR /usr/src/app
RUN cmake . && make
ENTRYPOINT ["./TinyServer"]
CMD ["80"]
EXPOSE 80