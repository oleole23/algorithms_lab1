FROM ubuntu as build
RUN apt update && install g++ -y 
WORKDIR app
COPY . .
RUN g++ main.cpp

FROM ubuntu
WORKDIR app
COPY --from=build /app/a.out ./a.out
CMD ./a.out
