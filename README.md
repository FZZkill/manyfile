# <center> MANYFILE </center>
> How many files in my project?
>
> ~~Where is my document?~~

~~However, This isn't why I wrote about it.~~

# Compile

C++ application need compiler on person.

So, We need compile this.

## Tools
1. This "README.md"
2. A C++ compiler (such as Clang, gcc)
3. cmake
4. Build tool (such as ninja, GNU Make)

Let's start!

## Build
First, You should to clone this repo.

Then use your tool to compile this.

And, It used some C++20 features feature...

### PowerShell

``` PowerShell
git clone https://github.com/fzzkill/manyfile.git --depth 1
cd manyfile
cmake build .
cmake --build .

```

### POSIX Shell

```Shell
git clone https://github.com/fzzkill/manyfile.git --depth 1
cd manyfile
cmake build .
cmake --build .
```

# Usage
> Running this program directly will cause a SigABRT error.

    Manyfile [arguments...]
    
    arguments:
        path [directory Path] p --
            default path is: './'
        regex [regex]  r --
            All supported regular grammars are as follows:
                icase
                nosubs
                optimize
                collate
                ECMAScript
                basic
                extended
                awk
                grep
                egrep
                polynomial
                multiline
            The default regular grammar is: basic
        expression [regex expression] e --
            A regular expression that satisfies the condition
            The default expression is: searching all files
        input i --
            The data from the STDIN
        output [path] o
            Store the results in a file
        help h -- list this

    For example:
        Manyfile path "./" regex ECMAScript expression ".*"
        Manyfile p "./" r ECMAScript e ".*"

> Running directly still doesn't work, please try adding parameters:
>   e ".*" 


# Feature
- [ ] Markdown in multiple languages.
- [ ] A more complete main program.
- [ ] Better looking Markdown.
- [x] List all file by regex.
- [ ] Find file by regex.
- [ ] Find info from input.
- [ ] Other regular expression syntax.
- [ ] Configure file.

# Something else

The project didn't do anything, it was relatively rudimentary.

After my high school entrance examination, thank you!

Of course, it will be updated if I have time.

## Thanks
[fzf](https://github.com/junegunn/fzf) Sources of inspiration.

[LMFSWS](https://github.com/Lone-Air/LMFSWS) Partial code reference.

[Neovim](neovim.io) What a modern editor!

### License
The Mozilla Public License Version 2.0 (MPLv2.0)
