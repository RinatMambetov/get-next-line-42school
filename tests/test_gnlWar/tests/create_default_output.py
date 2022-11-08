files = [
	'63_line',
	'63_line_nl',
	'64_line',
	'64_line_nl',
	'65_line',
	'65_line_nl',
	'baudelaire.txt',
	'bible.txt',
	'empty',
	'empty_one',
	'void.txt',
	'line.txt',
	'large_file.txt',
	'Mr._Justice_Maxell_by_Edgar_Wallace.txt',
	'many_lines',
	'one_big_fat_line.txt',
	'lorem_ipsum',
	'n.txt',
	'over_buffer',
	'simple',
	'multi_in_one',
	'expected_result',
]


for filename in files:
	with open(filename, 'rb') as f:
		data = f.read()
	#count1 = len([c for c in data if c == ord('\n')])
	if data:
		data = data.replace(b'\n', b'\n\n')
		if data[-1] != ord('\n'):
			data += b'\n'
	#count2 = len([c for c in data if c == ord('\n')])
	#print(filename, count1, count2)
	with open("default_%s.output" % filename, 'wb') as f:
		f.write(data)

