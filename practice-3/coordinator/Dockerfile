FROM gcc

WORKDIR /coordinator

COPY . /coordinator

RUN g++ -o myapp coordinator.cpp

CMD ["./myapp"]