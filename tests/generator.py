from unittest import result


n = int(input())
result = 1
for i in range(n):
    result = result * (i + 1)
print(result, end="")