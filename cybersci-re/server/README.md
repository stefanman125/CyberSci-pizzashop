```
docker build --tag reserver .
docker run -d --name reserver --restart always -p 4444:4444 reserver
```
