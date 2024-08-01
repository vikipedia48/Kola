# Kola
Visualizer for Ethereum debug_traceTransaction logs
Can read the debug_traceTransaction from a local file or by making a request to an RPC node (DEBUG methods must be enabled on the network). 

## Shortcuts
Use the A and D keys for moving between steps. Holding shift simultaneously moves by 10, ctrl moves by 50. 
Use the W and S keys for moving between 'Seek' results
Double clicking Lookup window jumps to that step. Double clicking Contract Calls window jumps to the first step in that thread.
Double clicking any Stack, Memory or Storage value copies it to clipboard.

## Lookup instructions
Steps can be filtered or seeked in the lookup window. A Lua script is used to find matches for your query. Variables that can be used in the script are:

```
opcode - name of this step's opcode
pushes_new_value - a new value which this step pushed onto the stack (or empty if it didn't)
index - index of this step
thread_index - index of this step's thread/contract call (see the Contract Calls window element)
thread_name - name of this step's thread/contract call (see the Contract Calls window element)
sets_storage_slot - boolean that indicates whether this step set the specified storage slot (example: if sets_storage_slot["ab77..."] == true then match = true end)
sets_storage_value - boolean that indicates whether this step set the specified value to any storage slot (example: if sets_storage_value["ab77..."] == true then match = true end)
sets_memory_slot - boolean that indicates whether this step set the specified memory slot (example: if sets_memory_slot["0x40"] == true or sets_memory_slot[5] == true then match = true end)
sets_memory_value - boolean that indicates whether this step set the specified value to any memory slot (example: if sets_memory_value["ab77..."] == true then match = true end)

match - boolean value that needs to be set to true by the user if the script's condition is met  
```


