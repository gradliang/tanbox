# 格式描述

## 基本数据类型
32位时的数据类型描述：

|类型名|大小(字节)|对齐(字节)|说明|
|--	|--	|--	|--	|
|Elf32_Addr|4|4|无符号的程序地址|
|Elf32_Off|4|4|无符号的文件偏移量|
|Elf32_Half|2|2|无符号的中号整数|
|Elf32_Word|4|4|无符号的整数|
|Elf32_Sword|4|4|带符号的整数|
|Elf32_Xword|8|8|无符号的长整数|
|Elf32_Sxword|8|8|带符号的长整数|
|unsigned char|1|1|无符号的小号整数|

64位时的数据类型描述：

|类型名|大小(字节)|对齐(字节)|说明|
|--	|--	|--	|--	|
|Elf64_Addr|8|8|无符号的程序地址|
|Elf64_Off|8|8|无符号的文件偏移量|
|Elf64_Half|2|2|无符号的中号整数|
|Elf64_Word|4|4|无符号的整数|
|Elf64_Sword|4|4|带符号的整数|
|Elf64_Xword|8|8|无符号的长整数|
|Elf64_Sxword|8|8|带符号的长整数|
|unsigned char|1|1|无符号的小号整数|

## ELF文件头
32位时的ELF头：
```
struct Elf32_Ehdr
{
  unsigned char e_ident[EI_NIDENT];     // ELF标记，包括魔数与其他信息
  Elf32_Half    e_type;                 // 文件类型
  Elf32_Half    e_machine;              // 机器类型
  Elf32_Word    e_version;              // ELF对象版本
  Elf32_Addr    e_entry;                // 程序入口点的相对虚拟地址RVA
  Elf32_Off     e_phoff;                // 程序头的文件偏移 
  Elf32_Off     e_shoff;                // 节表的文件偏移
  Elf32_Word    e_flags;                // 处理器特殊标志
  Elf32_Half    e_ehsize;               // ELF头的大小
  Elf32_Half    e_phentsize;            // 程序头数组每一项大小
  Elf32_Half    e_phnum;                // 程序头数组的项数
  Elf32_Half    e_shentsize;            // 节表数组每一项大小
  Elf32_Half    e_shnum;                // 节表数组的项数
  Elf32_Half    e_shstrndx;             // 字符串表在节表中的索引
};
```
64位时的ELF头：
```
struct Elf64_Ehdr
{
  unsigned char e_ident[EI_NIDENT];     // ELF标记，包括魔数与其他信息
  Elf64_Half    e_type;                 // 文件类型
  Elf64_Half    e_machine;              // 机器类型
  Elf64_Word    e_version;              // ELF对象版本
  Elf64_Addr    e_entry;                // 程序入口点的相对虚拟地址RVA
  Elf64_Off     e_phoff;                // 程序头的文件偏移 
  Elf64_Off     e_shoff;                // 节表的文件偏移
  Elf64_Word    e_flags;                // 处理器特殊标志
  Elf64_Half    e_ehsize;               // ELF头的大小
  Elf64_Half    e_phentsize;            // 程序头数组每一项大小
  Elf64_Half    e_phnum;                // 程序头的项数
  Elf64_Half    e_shentsize;            // 节表数组每一项大小
  Elf64_Half    e_shnum;                // 节表数组的项数
  Elf64_Half    e_shstrndx;             // 字符串表在节表中的索引
};
```

### ELF标记 - e_ident
下面表格的常数代表e_ident数组中的索引：

|索引名|索引值|描述|
|--	|--	|--	|
|EI_MAG0|0|文件标志，指向"\x7fELF"的魔数|
|EI_CLASS|4|文件类型|
|EI_DATA|5|数据编码|
|EI_VERSION|6|ELF格式版本|
|EI_OSABI|7|OS/ABI|
|EI_ABIVERSION|8|ABI版本|
|EI_PAD|9|补齐数据起始|
|EI_NIDENT|16|e_ident数组大小|

#### e_ident[EI_CLASS]

|值|宏|含义|
|--	|--	|--	|
|01|ELFCLASS32|32位ELF|
|02|ELFCLASS64|64位ELF|

#### e_ident[EI_DATA]

|值|宏|含义|
|--	|--	|--	|
|01|ELFDATA2LSB|Little Endian|
|02|ELFDATA2MSB|Big Endian|

#### e_ident[EI_VERSION]
表示ELF格式版本，必须为1

#### e_ident[EI_OSABI]
表示ABI的类型，tanbox-image映像必须使用值0x97

#### e_ident[EI_ABIVERSION]
指ABI的版本，必须为1

### ELF文件类型 - e_type
tanbox-image映像的文件类型必须为0x0002（可执行文件）或者0x0003（ 动态库）

### 机器类型 - e_machine
|值|CPU类型|
|--	|--	|
|0x0002|i386|
|0x003E|x64-64|

### ELF对象版本 - e_version
目前版本值必须为0x00000001

### 程序入口点 - e_entry
这里记录了程序的入口点。可执行文件必须有。动态库可以有，也可以不需要，不需要时为0。

### 程序头的文件偏移 - e_phoff
tanbox-image映像必须包含程序头

### 节表的文件偏移 - e_shoff

### 处理器特殊标志 - e_flags
必须为0

### ELF头的大小 - e_ehsize

### 程序头数组每一项大小 - e_phentsize

### 程序头的项数 - e_phnum

### 节表数组每一项大小 - e_shentsize

### 节表数组的项数 - e_shnum

### 字符串表在节表中的索引 - e_shstrndx

---

## 程序头

程序头数组的每一项定义如下：
32位映像程序头：
```
struct Elf32_Phdr
{
  Elf32_Word    p_type;			/* Segment type */
  Elf32_Off     p_offset;		/* Segment file offset */
  Elf32_Addr    p_vaddr;		/* Segment virtual address */
  Elf32_Addr    p_paddr;		/* Segment physical address */
  Elf32_Word    p_filesz;		/* Segment size in file */
  Elf32_Word    p_memsz;		/* Segment size in memory */
  Elf32_Word    p_flags;		/* Segment flags */
  Elf32_Word    p_align;		/* Segment alignment */
};
```
64位映像程序头：
```
struct Elf64_Phdr
{
  Elf64_Word    p_type;			/* Segment type */
  Elf64_Word    p_flags;		/* Segment flags */
  Elf64_Off     p_offset;		/* Segment file offset */
  Elf64_Addr    p_vaddr;		/* Segment virtual address */
  Elf64_Addr    p_paddr;		/* Segment physical address */
  Elf64_Xword   p_filesz;		/* Segment size in file */
  Elf64_Xword   p_memsz;		/* Segment size in memory */
  Elf64_Xword   p_align;		/* Segment alignment */
};
```






