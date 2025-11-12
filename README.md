# swtime
If you have been longing for a core util to help you manage Swatch (tm) Internet Time in Beats (tm), this is for you

# base 10 time

There are 86400 seconds in a day:

```
60 seconds     60 minutes     24 hours    86400 seconds
----------  X ------------ X ---------- = -------------
 1 minute        1 hour        1 day         1 day
```

Internet Time starts at 0 and works it's way up to 1000.

# compiling

` gcc -std=c89 -pedantic -Wall -o swtime swtime.c`

# usage
```
./swtime -?
Usage: swtime [epoch | beats | flags]
  --help, -?         Show this help message
  --beats-only       Output beats without '@' prefix
  --rfc              Convert beats (from stdin) to RFC 2822 date
  [epoch]            Convert epoch to Swatch .beats
  [stdin]            Pipe date or beats into swtime
bash-3.2$ date | ./swtime
@257
```
