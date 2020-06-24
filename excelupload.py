import gspread
from oauth2client.service_account import ServiceAccountCredentials


#Set up authroization to manage spreadsheet and login here
scope = [
	'https://spreadsheets.google.com/feeds',
	'https://www.googleapis.com/auth/drive'
]

# load account credentials as json
credentials = ServiceAccountCredentials.from_json_keyfile_name('cred.json', scope)

# Try to get authorized
gc = gspread.authorize(credentials)

# Create a new document
doc = gc.create('New Document')
# share the document with the email owner
doc.share('your_email@gmail.com', perm_type='user', role='owner')


# Adding a basic sheet
worksheet = doc.get_worksheet(0)

# Adding data to the first row
worksheet.insert_row(['ID', 'DATA'], 1)
# Adding data in loop
for i in range(10):
	worksheet.append_row([i, str(i) + ' Data'])
	print(i)





