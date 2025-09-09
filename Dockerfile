
FROM gcc:13

WORKDIR /app

COPY . /app

RUN gcc -o main main.c

CMD ["./main"]
