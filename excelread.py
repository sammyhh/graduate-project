import random



fn = names.get_first_name()
print(fn)
ln = names.get_last_name()

wb = load_workbook('nike.xlsx')
data = wb['Sheet1']
sheet = wb.active


last_row = sheet.max_row
while sheet.cell(column=1, row=last_row).value is None and last_row > 0:
    last_row -= 1
last_col_a_value = sheet.cell(column=1, row=last_row).value

print(last_col_a_value)