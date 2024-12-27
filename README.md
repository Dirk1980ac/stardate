# stardate

Displays the current stardate in Star Trek: The Next Generation notation

## Installation

```bash
make && sudo make install
```

## Usage

Running the program with no arguments will return the stardate for the current date and time:

```bash
stardate
echo -n "Captain's Log, Stardate "; stardate
```

You may also provide a custom date:

```bash
stardate -c "July 4, 1776"
stardate --calendar "July 4, 1776"
```

You may also provide a stardate and get a calendar date back:

```bash
stardate -s 0
stardate --stardate 0
```

## Acknowledgements

The algorithm is derived from the calculations on [trekguide.com](http://trekguide.com/Stardates.htm).

Also, all due credit to Star Trek, Gene Roddenberry, Q, etc.
