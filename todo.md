# Input checking

- Read input line by line

- Extract token delimited by space, with spacing also serve as token

- Check command format based on tokens, there will be a list of command templates (not template in
  C++) to test against. Each template will be a list of typename (STARTING_WORD, ID, AGE, NAME, NUM,
  SPACE) denoting the pattern to match for all available command.

- For each command, when matching against to template list, do:
    - Convert argument + test for correct type + test for correct value
    - Convert to correct command class
