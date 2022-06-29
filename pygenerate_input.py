import sys
id_block=sys.argv[1]
nbr_argument=int(sys.argv[2])
argument_repeted=[]
argument_nbr_repition=[]
argument_indices=[]
test="#in:\ninput.json\n#graphe:\nin["
nbr_block=0
input_block=[]
for arg in sys.argv[3:]:
    if( ":" in arg):
        tmp=arg.split(":")
        argument_repeted.append(tmp[0])
        argument_nbr_repition.append(int(tmp[1]))
        argument_indices.append(0)
    elif("[" not in arg):
        nbr_block =int(arg)
    else:
        input_block=arg.split("[")[1].split("]")[0].split(",")
        
            



for i in range(1,nbr_argument+1):
    if(str(i) in argument_repeted):
        indice=argument_repeted.index(str(i))
        for j in range (1,(argument_nbr_repition[indice]+1)):
            test=test+id_block+"."+str(i)+":"+str(j)+","
            
    else:
        test=test+id_block+"."+str(i)+","
test=test[0:len(test)-1]+"]\n"
for indice_block in range(1,nbr_block+1):
    test=test+id_block+str(indice_block)+"["
    iterateur=1
    for i in range(1,nbr_argument+1):
        if(str(i) in argument_repeted):
            
            indices=argument_repeted.index(str(i))
            test=test+"i0."+str(argument_indices[indices]+iterateur)+","
            argument_indices[indices]+=1
            iterateur=iterateur+argument_nbr_repition[argument_repeted.index(str(i))]
        else:
            test=test+"i0."+str(iterateur)+","
            iterateur=iterateur+1
    test=test[0:len(test)-1]+"];"
test=test[0:len(test)-1]+"\nout["
for i in range(0,nbr_block):
    test=test+id_block+str(i+1)+","
print(test[0:len(test)-1]+"]")
#python3 pygenerate_input.py 0 6 2:8 6:8 8 [1,2,3,4,5,6] >input.txt