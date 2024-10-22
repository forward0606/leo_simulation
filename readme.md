## input_graph
```
#total_nodes, #satellites, #timeslots
storage limit for each satellite

timeslot1:
#total link in timeslots
u, v, cap: link (u, v) is connected with data rate cap
```
all satellite id must smaller than user id 

## input_request
```
#requests
src, dst, data_volume, value, start, deadlines
```


## LP result
```
#channel assigned at timeslot 1
req_id, from, to
...

#channel assigned at timeslot 2
req_id, from, to, flow_size
...
```