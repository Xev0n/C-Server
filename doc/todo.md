# What does a HTTP server does
- Listens to HTTP requests on a host and port
- De-code the HTTP requests
    - Path
    - Content-type
    - Body
    - Action type (get, post, put, etc)
    - etc
- Returns a HTTP Response
- Handles error
    - malformatted request
    - malformated path
    - malformated body (ex: json)

