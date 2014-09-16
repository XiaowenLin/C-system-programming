#Sample Test
import parsort
import random,sys

def test(size, thread_count, max_point):
	print 'Running Test with Size:'+str(size)+'  Thread Count:'+str(thread_count)
	nums = [int(1000*random.random()) for i in xrange(size)]
	result = parsort.sort(nums, thread_count)
	result2 = sorted(nums, key=int)
	if(len(result)!=len(result2)):
		return False
	for i in range(len(result)):
		if result[i] != result2[i]:
			return False
	return True

point = 0
#small tests
if not test(10, 1, 1):
	sys.exit('Fail')
if not test(10, 2, 1):
	sys.exit('Fail')
if not test(10, 3, 2):
	sys.exit('Fail')
#large tests
if not test(1234567, 1, 2):
	sys.exit('Fail')
if not test(1234567, 10, 2):
	sys.exit('Fail')
if not test(1234567, 100, 2):
	sys.exit('Fail')
print 'Passed all tests'


