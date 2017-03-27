import csv
import numpy
import sys

csv_filename = sys.argv[1]

# Hash with (testcasename, results)
# Each test case result structure is a hash with (variantname, timings)
# Timings is a list of float values
test_cases = {}
versions = []
variants = []

with open(csv_filename) as csvfile:
	csv_reader = csv.reader(csvfile)
	for row in csv_reader:
		#print(', '.join(row))
		test_case_name = row[0]
		version_variant_names = row[1].split('_')
		timing = float(row[2])
		
		version_name = version_variant_names[0]
		variant_name = version_variant_names[1]
		
		if test_case_name not in test_cases:
			test_cases[test_case_name] = {}
			#print(test_case_name)
		
		test_case = test_cases[test_case_name]
		if version_name not in test_case:
			version_data = {}
			version_data['name'] = version_name
			version_data['best_variant'] = 'unknown'
			version_data['best_timing'] = 0.0
			version_data['variants'] = {}
			test_case[version_name] = version_data
			
			if version_name not in versions:
				versions.append(version_name)
			
		version_data = test_case[version_name]
		if variant_name not in version_data['variants']:
			variant_data = {}
			variant_data['name'] = variant_name
			variant_data['timings'] = []
			variant_data['timing'] = 0.0
			version_data['variants'][variant_name] = variant_data
			
			if variant_name not in variants:
				variants.append(variant_name)
		
		variant_data = version_data['variants'][variant_name]
		timings = variant_data['timings']
		timings.append(timing)

#print('Num test cases: {}'.format(len(test_cases)))
for test_case_name, test_case in test_cases.items():
	best_timing = 100000000.0
	best_variant = ''
	for version_name, version_data in test_case.items():
		for variant_name, variant_data in version_data['variants'].items():
			timings = variant_data['timings']
			timing = numpy.percentile(numpy.array(timings), 80)
			variant_data['timing'] = timing
			#print('{},{},{}'.format(test_case_name, variant_name, timing))
			if timing < best_timing:
				best_timing = timing
				best_variant = variant_name
		
			#print('Best variant for {}:{} is {}: {}'.format(test_case_name, version_data, best_variant, best_timing))
			version_data['best_variant'] = best_variant
			version_data['best_timing'] = best_timing
			
		# Pad any missing variants for this version
		for variant_name in variants:
			if variant_name not in version_data['variants']:
				variant_data = {}
				variant_data['name'] = variant_name
				variant_data['timings'] = []
				variant_data['timing'] = 0.0
				version_data['variants'][variant_name] = variant_data


# We print are data such that each row has the timings for each variant of a given version
# e.g. test case 1 v0
for test_case_name, test_case in test_cases.items():
	print('{},{}'.format(test_case_name, ','.join(variants)))
			
	for version_name, version_data in test_case.items():
		version_timings = []
		for variant_name in variants:
			variant_data = version_data['variants'][variant_name]
			timing = variant_data['timing']
			version_timings.append(str(timing))
		
		print('{},{}'.format(version_name, ','.join(version_timings)))
	
	print()
	print()
















