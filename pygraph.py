
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
def generate_block_function(id):
    block_function=dict()
    block_function["displayName"]="add"+str(id)
    block_function["id"]="add"+str(id)
    block_function["type"]="function"
    block_function["implementation"]=dict()
    block_function["implementation"]["pool"]= "CSITutorialPool"
    block_function["implementation"]["function"]= "csiAdd"
    block_function["implementation"]["version"]= 1
    return block_function
def create_struct_graphe():
    #first level
    graph=dict()

    graph["desc"]="Simulation of CVM paralel algorithm"
    graph["grammarVersion"]=3

        #impelemntation blocks
    graph["implementation"]=dict()
    graph["implementation"]["name"]="executionGraph"
    graph["implementation"]["version"]="1"

    graph["implementation"]["settings"]=dict()
    graph["implementation"]["settings"]["displayName"]="Graph"
    graph["implementation"]["settings"]["id"]="Graph"
    graph["implementation"]["settings"]["type"]="ExecutionGraph"
    graph["implementation"]["settings"]["implementation"]=dict()
    graph["implementation"]["settings"]["implementation"]["blocks"]=[]
    for i in range(0,4):
        graph["implementation"]["settings"]["implementation"]["blocks"].append(generate_block_function(i))
    graph["implementation"]["settings"]["implementation"]["controlFlows"]=[]
    graph["implementation"]["settings"]["implementation"]["dataFlows"]=[]


        #on call blocks
    graph["oncall"]=dict()
    graph["oncall"]["in"]=dict()
    graph["oncall"]["in"][ "parameters"]=[]


    graph["oncall"]["out"]=dict()
    graph["oncall"]["out"][ "parameters"]=[]
        #progress blocks
    graph["progress"]=dict()
    #throw blocks
    graph["throw"]=dict()
    return graph




graph=create_struct_graphe()    
pp = pprint.PrettyPrinter(indent=4)
#pp.pprint(graph)
print_string="{\n"
print_string=print_dict(graph,print_string,4,2)
print_string=print_string[:len(print_string)-2]
print(print_string)