# yacbrafi
Brainfuck interpreter written in C<br />
**y**et **a**nother **c** **bra**in**f**uck **i**nterpreter

# Features
- Executing a Brainfuck program given as a **file** or an **command line argument**
- Showing the currently executed command
- Showing the trace of the execution

# Compilation and Installation
Compile:
```
make
```
If you want to access **yacbrafi** on your entire system, copy it to `/usr/bin`:
```
sudo scp yacbrafi /usr/bin
```

# Usage

**yacbrafi** will check first if the program you have entered is correct before executing it.<br /> Correct means that it the same amount of \[ and \].

## Options
**yacbrafi** comes with the following command line options:

<table>
  <tr>
    <td><code>-f &lt;file path&gt;</code></td>
    <td>Read the Brainfuck program from a file</td>
  </tr>

  <tr>
    <td><code>-c</code></td>
    <td>Output as <code>char</code> and not as <code>int</code></td>
  </tr>

  <tr>
    <td><code>-pt</code></td>
    <td><b>p</b>rint <b>t</b>race<br>Print the sequence in which the commands were executed.</td>
  </tr>

  <tr>
    <td><code>-pap</code></td>
    <td><b>p</b>rint <b>a</b>ctive <b>p</b>osition<br>Print the command and highlight the currently executed command</td>
  </tr>
</table>

**The order of the command line options doesn't matter!**

## Supplying the program
The program can either be supplied by adding it as a **command line argument**...
```
yacbrafi "++[>++[>++<-]<-]"
```
... or by **giving the file path** as a command line argument after the parameter `-f`:
```
yacbrafi -f /path/to/programm.bf
```
