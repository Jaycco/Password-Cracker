from collections import Counter

with open("common_passwords.txt") as f:
    c = Counter()
    for x in f:
        c += Counter(x.strip())

print(c)
print(len(c))
print(sorted(dict(c)))
print(sorted(c.items(), key = lambda kv:(kv[1], kv[0]), reverse = True))
v = sorted(c.items(), key = lambda kv:(kv[1], kv[0]), reverse = True)
print(type(v))
value = ""
for i in v:
    value = value + i[0]
print(value)