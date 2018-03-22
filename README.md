usage: ./switch in_file out_file
in_file should contain operations available on switches:
  add [id] [name] [IP] [mode] [id_stack] [type]
    mode can be:
      SINGLE - works individually
      STACK - works in a stack
    type is available only for STACK mode and can be:
      NON_BASE - secondary switch
      BASE - primary switch (this is located on the base of the switch)
  del id
  set [id] [mode] [id_stack] [type]
  ipmin
    shows the minimum ip value in the network(it is converted to a decimal value)
  show
    shows the id of every single switch on a line and the id of every stack followed by the switches
    contained in it
out_file contain the output of ipmin and show commands
