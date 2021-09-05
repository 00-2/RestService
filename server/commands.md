 curl -X POST "http://localhost:8000/users" -H  "accept: application/json" -H  "Content-Type: application/json" -d "{\"login\":\"string1\",\"password\":\"string1\"}"
 curl -X GET "http://localhost:8000/users/1"
 curl -X DELETE "http://localhost:8000/users/1"
