import glob

def is_utf8_file_with_bom(filename):
    '''utf-8 ファイルが BOM ありかどうかを判定する
    '''
    line_first = open(filename, encoding='utf-8').readline()
    return (line_first[0] == '\ufeff')

def convert(file_name):
    with open(file_name, mode="r+", encoding="utf-8", newline='\n') as f:
        original = f.read()
        f.seek(0)
        f.write('\ufeff')
        f.write(original)

src1 = glob.glob("*.hpp")
src2 = glob.glob("*.cpp");
src3 = glob.glob("BattleScene/*")
#src.remove('encoding.py')

for i in src1:
    if(not is_utf8_file_with_bom(i)):
        print(i)
        convert(i)
for i in src2:
    if(not is_utf8_file_with_bom(i)):
        print(i)
        convert(i)
for i in src3:
    if(not is_utf8_file_with_bom(i)):
        print(i)
        convert(i)

