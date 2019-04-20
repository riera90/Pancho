FROM gcc:8.2
ADD . /app
WORKDIR /app
RUN make clean
RUN make config
RUN make
CMD ./output/bin.out
