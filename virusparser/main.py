import sys

DEFAULT_FILE = "infections.txt"

if __name__ == '__main__':
    file_name = DEFAULT_FILE
    if len(sys.argv) > 1:
        file_name = sys.argv[1]
    data = None
    with open(file_name) as f:
        data = f.readlines()

    symptom_list = []
    curr_symptom = {}
    is_parsing = False
    
    for line in data:
        if line.startswith("!"):
            is_parsing = True
            curr_symptom["name"] = line[1:-1]
            continue
        if is_parsing:
            is_parsing = False
            items = line.split("|")
            curr_symptom["stealth"] = int(items[1])
            curr_symptom["resistance"] = int(items[3])
            curr_symptom["stage speed"] = int(items[5])
            curr_symptom["transmission"] = int(items[7])
            symptom_list.append(curr_symptom)
            curr_symptom = {}
    
    with open("symptoms.c", "w") as out_file:
        out_file.write("// THIS IS GENERATED CODE!\n")
        out_file.write("#include \"symptoms.h\"\n")
        out_file.write("const struct Symptom symptoms[NUM_SYMPTOMS] = {\n")
        for symptom in symptom_list:
            out_file.write("    {\n")
            out_file.write(f"        .name = \"{symptom['name']}\",\n")
            out_file.write(f"        .stealth = {symptom['stealth']},\n")
            out_file.write(f"        .resistance = {symptom['resistance']},\n")
            out_file.write(f"        .stage_speed = {symptom['stage speed']},\n")
            out_file.write(f"        .transmission = {symptom['transmission']}\n")
            out_file.write("    },\n")
        out_file.write("};\n")