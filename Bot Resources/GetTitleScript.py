import json
import urllib.request
from bs4 import BeautifulSoup
from tqdm import tqdm

def get_website_title(url):
    req = urllib.request.Request(url)
    req.add_header('User-Agent','Mozilla/5.0')
    content = urllib.request.urlopen(req)
    soup = BeautifulSoup(content, "lxml")
    return soup.title.string

def find_total():
    total = 0
    for i in list(data.values()):
        for j in list(i.values()): 
            if isinstance(j,list):
                for k in j:
                    if k.startswith('http'):
                        total += 1
    else:
        return total

with open('resources.json') as f:
    data = json.load(f)

total = find_total()
pbar = tqdm(range(total))
for i in data.values():
    for j,k in i.items():
        for count,l in enumerate(k):
            if l.startswith('https') and len(l.split(' - ')) == 1:
                try:
                    title = get_website_title(l)
                except:
                    title = ''
            
                k[count] = f"{title} - {l}" if title else l
                pbar.update(1)
else:
    pbar.close()

obj = json.dumps(data, indent=4)
with open('dummy.json','w') as f:
    f.write(obj)

print('Task done')