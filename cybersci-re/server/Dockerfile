FROM golang:latest

COPY ./reserver.go /

EXPOSE 4444

RUN go build -o /reserver /reserver.go

# Command to run the executable
ENTRYPOINT ["/reserver"]
