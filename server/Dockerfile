FROM gcc:8.2
RUN apt update -y
RUN apt upgrade -y
RUN apt install -y cmake
ADD . /app
WORKDIR /app/build
CMD cmake .. && /app/build/panchoServer.out