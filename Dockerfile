FROM ubuntu as build
WORKDIR app
RUN apt update && apt install g++ -y
COPY . .
RUN g++ main.cpp

FROM ubuntu
WORKDIR app
COPY --from=build /app/a.out ./my_app.out
CMD ./my_app.out
