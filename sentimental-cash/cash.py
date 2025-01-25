from cs50 import get_float
money = int(get_float("Change: ") * 100)
while money < 0:
    money = int(get_float("Change: ") * 100)
cnt1 = money // 25
money -= cnt1 * 25
cnt2 = money // 10
money -= cnt2 * 10
cnt3 = money // 5
money -= cnt3 * 5
cnt4 = money
print(cnt1 + cnt2 + cnt3 + cnt4)
