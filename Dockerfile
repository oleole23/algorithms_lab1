FROM ubuntu as build
WORKDIR app
COPY . .
RUN g++ main.cpp

FROM ubuntu
WORKDIR app
COPY --from=build /app/a.out ./a.out
CMD ./a.out
