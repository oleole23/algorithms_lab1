FROM ubuntu as build
RUN apt update && install g++ -y 
COPY . .
RUN g++ main.cpp

FROM ubuntu
COPY --from=build ./a.out ./a.out
CMD ./a.out
