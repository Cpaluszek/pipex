# pipex
This project aims to deepen your understanding of the two concepts: Redirections and Pipes.<br/>
It is an introductory project for the bigger UNIX projects that will appear later on in the cursus.

## Mandatory part
The pipex program must behave exactly the same as the shell command below:
This:<br/>
`./pipex file1 cmd1 cmd2 file2`

Should behave like:<br/>
`< file1 cmd1 | cmd2 > file2`

## Bonus part

#### Pipex should handle multiple pipes.
This:<br/>
`./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`

Should behave like:<br/>
`< file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2`


#### Support « and » when the first parameter is "here_doc".
This:<br/>
`./pipex here_doc LIMITER cmd1 cmd2 file2`

Should behave like:<br/>
`cmd1 << LIMITER | cmd2 >> file2`
