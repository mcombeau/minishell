# Parsing Tests

## TODO

Failed tests: 38. 39. 40. 47. 50. 52. 53. 54. 60. 61. 66.

Further testing required: 49.

Test again when infile/outfile working: 51.

Test again when pipes working: 63. 67. 68. 70.

## Test list

1. `ec""ho test`
	-> OK
2. `""echo test`
	-> OK
3. `echo"" test`
	-> OK
4. `echo "" test`
	-> OK
5. `echo $USER`
	-> OK
6. `echo $USE""R`
	-> OK
7. `echo ""$USER`
	-> OK
8. `echo "$"USER`
	-> OK
9. `echo  $""USER`
	-> OK
10. `ec''ho test`
	-> OK
11. `''echo test`
	-> OK
12. `echo'' test`
	-> OK
13. `echo '' test`
	-> OK
14. `echo $USER`
	-> OK
15. `echo $USE''R`
	-> OK
16. `echo ''$USER`
	-> OK
17. `echo '$'USER`
	-> OK
18. `echo  $''USER`
	-> OK
19. `echo $`
	-> OK
20. `echo $""`
	-> OK
21. `echo "" "" "" test`
	-> OK
22. `echo """""" test`
	-> OK
23. `echo $USER"" ''`
	-> OK
24. `ls ""`
	-> OK
25. `ls '"`
	-> OK (bash opens heredoc, minishell does not but error messages match)
26. `ls "'`
	-> OK (see  25)
27. `ls "    "`
	-> OK
28. `ls "  ' "`
	-> OK
29. `"ls"`
	-> OK
30. `l"s"`
	-> OK
31. `ls"" -la`
	-> OK
32. `ls "" -la`
	-> OK
33. `ls """"-la`
	-> OK
34. `ls ""-la`
	-> OK
35. `echo test""test`
	-> OK
36. `echo test"" test`
	-> OK
37. `echo test ""test`
	-> Ok
38. `echo test "'"test`

	-> Does not match bash:
	* minishell result: `test test`,
	* bash result: `test 'test`

39. `echo $$$USER`

	-> Does not match bash: 
	* minishell result: `$$username`, 
	* bash result: `13435username` (bash interprets it as `$$` + `$USER`)

40. `echo $$USER`

	-> Does not match bash: 
	* minishell result: `$username`, 
	* bash result: `13435USER` (see 39.)

41. `echo $USER$USER`
	-> OK
42. `echo $USER""$USER`
	-> OK
43. `echo $USER" "$USER`
	-> OK
44. `echo "|" ls`
	-> OK
45. `echo test$1test`
	-> OK
46. `echo test$INEXISTANT_VAR`
	-> OK
47. `echo "$USER>>"`

	-> Does not match bash:
	* minishell result: `\n`,
	* bash result: `username>>`

48. `echo "$USER11111fjfjfjf"`
	-> OK
49. `echo $\"echo`

	-> Does not match bash:
	* minishell result: `syntax error`,
	* bash result: `"echo`
	-> This is normal behavior for minishell. TODO: Check if error code -2 on exit.

50. `echo "test$<test"`

	-> Does not match bash:
	* minisell result: `test`
	* bash result: `test$<test`

51. `echo test$<test`

	-> minishell crash! (This is probably due to infiles not working yet)

52. `echo "test$-r"`

	-> Does not match bash:
	* minishell result: `test`
	* bash result: `testhimBHsr`

53. `echo "test$-?"`

	-> Does not match bash:
	* minishell result: `test`
	* bash result: `testhimBHs?`

54. `echo $-1$USER`

	-> Does not match bash:
	* minishell result: `username`
	* bash result: `himBHs1master`

55. `echo $1`
	-> OK
56. `echo "$1"`
	-> OK
57. `echo  $"USER"`
	-> OK
58. `echo  $'USER'`
	-> OK
59. `echo "$NULL" test`
	-> OK
60. `echo '"abc"'`

	-> Does not match bash:
	* minishell result: `abc`
	* bash result: `"abc"`

61. `echo '  "abc" '`

	-> Does not match bash:
	* minishell result: `abc`
	* bash result: `"abc"`

62. `echo $NULL test`
	-> OK
63. `echo test |cat`

	-> Minishell crash! Because pipes not implemented yet

64. `echo koala ||| cat`
	-> OK
65. `export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8`
	-> OK
66. `echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H"`

	-> Does not match bash:
	* minishell result: `\n`
	* bash result: `1'2$C"$D5"$F"'7'8`


67. `echo " $ " | cat -e`

	-> Minishell crash: pipes not implemented yet

68. `echo $:$= | cat -e`

	-> Minishell crash: pipes not implemented yet

69. `export FOO=' " '`
	-> OK
70. `echo " $FOO " | cat -e`
	-> Minishell crash: pipes not implemented yet

---
Thanks to okushnir for tests.