
from copy import deepcopy
import json
import pprint
def print_block(array,print_string,space,incrementation):
    for i in range(0,len(array)):
        print_string=print_string+space*" "+"{\n"
        print_string=print_dict(array[i],print_string,space+incrementation,incrementation)
       
    return print_string    
def print_dict(graph,print_strings,space,incrementation):
    print_string = print_strings
    test=dict()
    test_array=[]
    for key, value in graph.items():
        
        
        if(type(value)==type(test)):
            print_string=print_string+space*" "+'"'+key+'"'+":"+"{\n"
            print_string=print_dict(value,print_string,(space+incrementation),incrementation)
        elif(type(value)==type(test_array)):
            
            print_string=print_string+space*" "+('"'+key+'"'+":[\n") 
            print_string=print_block(value,print_string,(space+incrementation),incrementation)
            if(print_string[len(print_string)-2]==","):
                print_string=print_string[:len(print_string)-2]
                print_string=print_string+"\n"
            print_string=print_string+space*" "+("],\n")        
        else:
            print_string=print_string+space*" "+('"'+key+'"'+":"+'"'+str(value)+'"'+",\n")
    if(print_string[len(print_string)-2]==","):
        print_string=print_string[:len(print_string)-2]
        print_string=print_string+"\n"
    print_string=print_string+(space-incrementation)*" "+("},\n")
    return print_string
def generate_block_function(block,id):
    block_function=dict()
    block_function["displayName"]=block["displayName"]+str(id)
    block_function["id"]=block["id"]+str(id)
    block_function["type"]=block["type"]
    block_function["implementation"]=block["implementation"]
    return block_function
def create_struct_graphe(blocks_function,input,dataFlows,controlFlows,output_graphe,nbr_syncrho):
    #first level
    graph=dict()

    graph["desc"]="Simulation of CVM paralel algorithm"
    graph["grammarVersion"]=3

        #impelemntation blocks
    graph["implementation"]=dict()
    graph["implementation"]["name"]="executionGraph"
    graph["implementation"]["version"]=1

    graph["implementation"]["settings"]=dict()
    graph["implementation"]["settings"]["displayName"]="Graph"
    graph["implementation"]["settings"]["id"]="graph"
    graph["implementation"]["settings"]["type"]="ExecutionGraph"
    graph["implementation"]["settings"]["implementation"]=dict()
    graph["implementation"]["settings"]["implementation"]["blocks"]=blocks_function
    test={

                "displayName": "Wait all",
  
                "id": "join",
  
                "type": "Logical",
  
                "implementation": {
  
                  "nbPorts": nbr_syncrho,
  
                  "mode": "waitAll"
  
                }
  
              }
    graph["implementation"]["settings"]["implementation"]["blocks"].append(test)
    graph["implementation"]["settings"]["implementation"]["controlFlows"]=controlFlows
    graph["implementation"]["settings"]["implementation"]["dataFlows"]=dataFlows
    graph["implementation"]["settings"]["implementation"]["runtimeSettings"]=dict()
    graph["implementation"]["settings"]["implementation"]["runtimeSettings"][ "directData"]=True

        #on call blocks
    graph["onCall"]=dict()
    graph["onCall"]["in"]=dict()
    graph["onCall"]["in"][ "parameters"]=input
    graph["onCall"]["out"]=dict()
    graph["onCall"]["out"][ "parameters"]=output_graphe
    
     
          

  
        #progress blocks
    graph["progress"]=dict()
    #throw blocks
    graph["throwError"]=dict()
    graph["throwError"]["type"]="CSIExecGraphError"

    return graph
def read_input(text,i,step,cpt,csifunction,input_blocks,output_blocks,graph_input):
    if(cpt==0):
        with open(text[i]) as json_file:
            data = json.load(json_file)
        blocks=[]
        block_input=[]
        block_output=[]
        indice=0
        for i in range(0,len(data["block"])):
            blocks.append(dict())
            blocks[indice]["displayName"]=data["block"][i]["function"].replace("csi","").lower()
            blocks[indice]["id"]=data["block"][i]["function"].replace("csi","").lower()
            blocks[indice]["type"]=data["block"][i]["type"]
            blocks[indice]["implementation"]=dict()
            blocks[indice]["implementation"]["pool"]=data["block"][i]["pool"]
            blocks[indice]["implementation"]["function"]=data["block"][i]["function"]
            blocks[indice]["implementation"]["version"]=data["block"][i]["version"]
            csi_function_file=data["block"][i]["function"]+"_v"+str(data["block"][i]["version"])+".json"
            with open(csi_function_file) as json_file:
                    inout = json.load(json_file)
            block_input.append(inout["onCall"]["in"]["parameters"])
            block_output.append(inout["onCall"]["out"]["parameters"])
            
            indice=indice + 1

        return blocks,block_input,block_output
    elif(cpt==1):
        dataFlows=[]
        controlFlows=[]
        input_graphe=graph_input
        output_graphe=[]
        blocks=[]
        for j in range(i,len(text)):
            if( "in" in text[j]):
                input=text[j].split("[")[1].split("]")[0]
                
                if(":"not in input):
                    csifunctionid=int(input)
                    block_id=int(text[j].split("[")[1].split("]")[0])
                    csi_function_file=csifunction[block_id]["implementation"]["function"]
                    csi_function_file=csi_function_file+"_v"+str(csifunction[csifunctionid]["implementation"]["version"])+".json"
                    with open(csi_function_file) as json_file:
                        data = json.load(json_file)
                    input_graphe=data["onCall"]["in"]["parameters"]
                    
                    #functions dataFlows
                    #a changer
                    diffrent=0
                    ###
                    for input in input_graphe:
                        
                        dataflow_block=dict()
                        dataflow_block["from"]="graph.call."+input["label"]
                        dataflow_block["to"]=csifunction[block_id]["id"]+"0.call."+input["label"]
                        dataFlows.append(dataflow_block)
                        if(diffrent==0):
                            controlFlows_block=dict()
                            controlFlows_block["from"]="graph.call"
                            controlFlows_block["to"]=csifunction[block_id]["id"]+"0.call"
                            controlFlows.append(controlFlows_block)
                            diffrent=1
                        
                    blocks.append(generate_block_function(csifunction[block_id],0))
                else:
                    temp=input.split(",")
                    for input_graph in temp:
                        id_block=input_graph.split(".")[0]
                        id_label=input_graph.split(".")[1].split(":")[0]
                        id_input=""
                        
                        if(":" in input_graph):
                            id_input=input_graph.split(":")[1]
                        graph_parameter=deepcopy(input_blocks[int(id_block)][int(id_label)-1])
                        graph_parameter["label"]=input_blocks[int(id_block)][int(id_label)-1]['label']+id_input
                        input_graphe.append(graph_parameter)

                    
            elif("out" in text[j]):
                
                input_block=text[j].split("[")[1].split("]")[0].split(",")
                indice_input=0
                diffrent_block=[]
                different=0
                for input in input_block:
                    if("." in input):
                        id=int(input.split(".")[0][0])
                        indice_output=int(input.split(".")[1])
                        dataflow_block=dict()
                        if(input.split(".")[0][1:] not in diffrent_block):
                            diffrent_block.append(input.split(".")[0][1:])
                            controlFlows_block=dict()
                            controlFlows_block['from']=csifunction[id]["id"]+input.split(".")[0][1:]+".success"
                            controlFlows_block["to"]="join.call"
                            controlFlows.append(controlFlows_block)    
                        dataflow_block["from"]=csifunction[id]["id"]+input.split(".")[0][1:]+".success."+output_blocks[id][indice_output-1]["label"]
                        dataflow_block["to"]="graph.success."+csifunction[id]["id"]+input.split(".")[0][1:]+"_"+output_blocks[id][indice_output-1]["label"]
                        
                        dataFlows.append(dataflow_block)
                        indice_input+=1
                        
                    else:
                        id=int(input[0])
                        if(different==0):
                            controlFlows_block=dict()
                            controlFlows_block['from']=csifunction[id]["id"]+input[1:]+".success"
                            controlFlows_block["to"]="join.call"
                            controlFlows.append(controlFlows_block)


                             
                        
                        for output in output_blocks[id]:
                            dataflow_block=dict()
                            dataflow_block["from"]=csifunction[id]["id"]+input[1:]+".success."+output["label"]
                            dataflow_block["to"]="graph.success."+csifunction[id]["id"]+input[1:]+output["label"]
                            temp_output=deepcopy(output)
                            temp_output["label"]=csifunction[id]["id"]+input[1:]+output["label"]
                            output_graphe.append(temp_output)
                            dataFlows.append(dataflow_block)
                        indice_input+=1
                controlFlows_block=dict()
                controlFlows_block['from']="join.success"
                controlFlows_block["to"]="graph.success"
                controlFlows.append(controlFlows_block)  
                    
                """        
                for output in input_block:
                    if("." in output):
                        print("partial:",output)
                    else:
                        print("complete",output)
                """

                
            else:
                block=text[j].split(";")
                for k in range(0,len(block)):
                    block_info=block[k].split("[")
                    block_id=block_info[0]
                    blocks.append(generate_block_function(csifunction[int(block_id[0])],int(block_id[1:])))
                    input_block=block_info[1].split("]")[0].split(",")
                    
                    indice_input=0
                    diffrent_block=[]
                    for input in input_block:
                        
                        if("i" in input.split(".")[0]):
                            id=int(input.split(".")[0].replace("i",""))
                            indice_output=int(input.split(".")[1])
                            dataflow_block=dict()
                            if(input.split(".")[0][1:] not in diffrent_block):
                                diffrent_block.append(input.split(".")[0][1:])
                                controlFlows_block=dict()
                                controlFlows_block['from']="graph.call"
                                controlFlows_block["to"]=csifunction[int(block_id[0])]["id"]+block_id[1:]+".call"
                                controlFlows.append(controlFlows_block)    
                            dataflow_block["from"]="graph.call."+graph_input[indice_output-1]["label"]
                            dataflow_block["to"]=csifunction[id]["id"]+block_id[1:]+".call."+input_blocks[id][indice_input]["label"]
                            dataFlows.append(dataflow_block)
                            indice_input+=1
                        else:
                            id=int(input.split(".")[0][0])
                            indice_output=int(input.split(".")[1])
                            dataflow_block=dict()
                            if(input.split(".")[0][1:] not in diffrent_block):
                                diffrent_block.append(input.split(".")[0][1:])
                                controlFlows_block=dict()
                                controlFlows_block['from']=csifunction[id]["id"]+input.split(".")[0][1:]+".success"
                                controlFlows_block["to"]=csifunction[id]["id"]+block_id[1:]+".call"
                                controlFlows.append(controlFlows_block)    
                            dataflow_block["from"]=csifunction[id]["id"]+input.split(".")[0][1:]+".success."+output_blocks[id][indice_output-1]["label"]
                            dataflow_block["to"]=csifunction[id]["id"]+block_id[1:]+".call."+input_blocks[id][indice_input]["label"]
                            dataFlows.append(dataflow_block)
                            indice_input+=1
            
        return input_graphe,blocks,dataFlows,controlFlows,output_graphe
                
                



filin = open("input.txt", "r")
text=filin.read().split("\n")
step=["#in:","#graphe:"]
step_cpt=0
list_input=[]
csifunction=[]
input_csifunction=[]
output_csifunction=[]
input_graphe=[]
output_graphe=[]
for i in range(0,len(text)):
    if(step[0]==text[i]):
        csifunction,input_csifunction,output_csifunction=read_input(text,i+1,step,0,csifunction,input_csifunction,output_csifunction,input_graphe)
        #print(csifunction)
        #print(input_csifunction)
        #print(output_csifunction)
    elif(step[1]==text[i]):
        input_graphe,block,dataFlows,controlFlows,output_graphe=read_input(text,i+1,step,1,csifunction,input_csifunction,output_csifunction,input_graphe)
        
       

graph=create_struct_graphe(block,input_graphe,dataFlows,controlFlows,output_graphe,8)    
pp = pprint.PrettyPrinter(indent=4)
#pp.pprint(graph)
print_string="{\n"
print_string=print_dict(graph,print_string,4,2)
print_string=print_string[:len(print_string)-2]
result = json.dumps(graph, indent = 3)
print(result)
