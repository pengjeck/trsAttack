//TRS曲线各标志位信息见PDF文件APPENDIX H:Trace Set Coding
//“TRS曲线.zip”文件解压后的TRS曲线文件可用uedit64等十六进制编辑工具打开，对照PDF文件查看标志位的含义
转换生成一个文件夹，文件夹包含：
1.wave.txt文件，存储trace中各Sample Y-axis的数值，一条trace存储一行
2.data.txt文件，存储每个trace的cryptographic data，一条trace对应data存储一行
3.info.txt文件，存储Header Coding包含的信息，如Figure H.1对应的info.txt为
	Trace Number： 	987；
	Samples Number：1000；
	...
