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
|EI_NIDENT|16|e_ident数组大小，常数|

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
表示ABI的类型，tanbox-image映像必须使用值0x02。 （抢了NetBSD的标志）

#### e_ident[EI_ABIVERSION]
指ABI的版本，必须为1

### ELF文件类型 - e_type
tanbox-image映像的文件类型必须为0x0002（可执行文件），0x0003（动态库）

### 机器类型 - e_machine
|值|CPU类型|
|--	|--	|
|3|i386|
|40|ARM|
|62|x64-64|
|183|ARM AARCH64|
|243|RISC-V|

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
  Elf32_Word    p_type;         // 段的类型
  Elf32_Off     p_offset;       // 段在文件中的偏移
  Elf32_Addr    p_vaddr;        // 段在内存中的虚拟地址
  Elf32_Addr    p_paddr;        // 段在内存中的物理地址，保留给用物理地址的系统使用
  Elf32_Word    p_filesz;       // 段在文件中的大小，以字节计算
  Elf32_Word    p_memsz;        // 段在内存中的大小，以字节计算
  Elf32_Word    p_flags;        // 段标志
  Elf32_Word    p_align;        // 段对齐，必须是2的次幂
};
```
64位映像程序头：
```
struct Elf64_Phdr
{
  Elf64_Word    p_type;         // 段的类型
  Elf64_Word    p_flags;        // 段标志
  Elf64_Off     p_offset;       // 段在文件中的偏移
  Elf64_Addr    p_vaddr;        // 段在内存中的虚拟地址
  Elf64_Addr    p_paddr;        // 段在内存中的物理地址，保留给用物理地址的系统使用
  Elf64_Xword   p_filesz;       // 段在文件中的大小，以字节计算
  Elf64_Xword   p_memsz;        // 段在内存中的大小，以字节计算
  Elf64_Xword   p_align;        // 段对齐，必须是2的次幂
};
```

### p_type: 段的类型

|段类型|值|描述|
|--	|--	|--	|
|PT_NULL|0|不使用|
|PT_LOAD|1|可装载段，段的文件占用大小由p_filesz指定，段的内存占用大小由p_memsz指定。如果p_memsz大于p_filesz，则额外部分用0填充。p_filesz不能大于p_memsz。多个PT_LOAD应该以p_vaddr升序排列|
|PT_DYNAMIC|2|动态连接表 (tanbox不使用)|
|PT_INTERP|3|动态链接器文件名（全路径）|
|PT_NOTE|4|笔记段，用来标记编译器信息|
|PT_SHLIB|5|保留|
|PT_PHDR|6|程序头表（就是程序头自己本身）|
|PT_TLS|7|线程局部存储段|
|PT_NUM|8|Number of defined types|
|PT_FIXUP|1981|基地址重定位表|
|PT_RESOURCE|1991|资源数据|
|PT_LTSYM|1997|装载时符号表|
|PT_IMPREL|1998|导入重定位信息表|


### p_flags: 段标志
|段对齐|值|描述|
|--	|--	|--	|
|PF_X|0x01|段可执行|
|PF_W|0x02|段可写|
|PF_R|0x04|段可读|

---
## PT_NOTE
PT_NOTE段只要记录了一些编译器信息，tanbox-image映像使用JSON文本串来记录编译器链接器的信息。

---
## PT_FIXUP 基地址重定位表
基地址重定位表跟Windows PE文件的差不多，并在此基础上做了修改增强。
基地址重定位表描述如下：

32位映像程序的基地址重定位表：
```
struct Elf32_Fixbase
{
  Elf32_Off     f_pgnum;                // 页的个数
  Elf32_Off     f_fixnum;               // 重定位的个数
  Elf32_Word    f_pgsize;               // 每页的大小，不大于64KB
  Elf32_Word    f_reserve;              // 保留
  
  struct Elf32_fixpageinfo 
  {
    Elf32_Addr  f_pgstart;                      // 该页的起始地址
    Elf32_Off   f_startidx;                     // 该页的重定位在装配表的起始索引号
    Elf32_Off   f_endidx                        // 该页的重定位在装配表的结束索引号
  }             f_pginfo[f_pgnum];      // 页表，数组项数由f_pgnum决定
  
  Elf32_Half    f_fixtab[f_fixnum];     // 装配表，数组项数由f_fixnum决定
};
```
64位映像程序的基地址重定位表：
```
struct Elf64_Fixbase
{
  Elf64_Off     f_pgnum;                // 页的个数
  Elf64_Off     f_fixnum;               // 重定位的个数
  Elf32_Word    f_pgsize;               // 每页的大小，不大于64KB
  Elf32_Word    f_reserve;              // 保留
  
  struct Elf64_fixpageinfo 
  {
    Elf64_Addr  f_pgstart;                      // 该页的起始地址
    Elf64_Off   f_startidx;                     // 该页的重定位在装配表的起始索引号
    Elf64_Off   f_endidx                        // 该页的重定位在装配表的结束索引号
  }             f_pginfo[f_pgnum];      // 页表，数组项数由f_pgnum决定
  
  Elf64_Half    f_fixtab[f_fixnum];     // 装配表，数组项数由f_fixnum决定
};
```

例如，一个代码页，它在装配表中开始索引为10086，一共有10个地址需要做基址重定位，则f_startidx的值为10086，f_endidx的值为10096。

### 装配表
装配表实际上就是一个2字节整数的数组。其组成根据不同的CPU类型，会有不同的结构。

### 装配表 - i386
i386的装配表中，数组每一项的2字节整数，全部位都是用于表示装配位置在页中的偏移量。装配目标是一个32位地址。

### 装配表 - x86-64
x86-64的装配表中，数组每一项的2字节整数，全部位都是用于表示装配位置在页中的偏移量。装配目标是一个64位地址。

---
## PT_RESOURCE 资源数据
资源数据实际上存储为一个打包好TBA文件，原封不动地存在PT_RESOURCE段中

---
## PT_LTSYM 装载时符号表
装载时符号表，字面意思是指模块被装载时，整个模块给装载器暴露使用的符号表。
可以把所有全局变量都放到装载时符号表，这样省时省力；也可以指定某些真正需要的符号放在装载时符号表，省点存储空间以及加快模块装载速度与符号搜索速度。

装载时符号表组成结构如下：

|字段|大小|说明|
|--	|--	|--	|
|s_symnum|Elf32_Word|符号个数，下面用N代表|
|s_flag|Elf32_Word|标志，保留，必须为0|
|s_dsoname|Elf32_Addr/Elf64_Addr|指向dso文件名字符串的地址|
|s_expaddrs [ ]|Elf32_Addr/Elf64_Addr * N|符号对应的地址表 (注:第0个符号地址为NULL，作占位)|
|s_names [ ]|Elf32_Addr/Elf64_Addr * N|符号名对应的地址表 (注:第0个符号指向"\0"，作占位)|
|s_nbucket|Elf32_Word|哈希表中bucket的个数，bucket [hashkey % nbucket]保存第0个可能匹配的符号的索引和chain表中可能的下一个符号的索引|
|s_bucket[0]|Elf32_Word|bucket[0]中第0个可能匹配的符号的索引|
|s_bucket[1]|Elf32_Word|bucket[1]中第0个可能匹配的符号的索引|
|...|...|...|
|s_bucket [s_nbucket - 1]|Elf32_Word|bucket[s_nbucket - 1]中第0个可能匹配的符号的索引|
|chain[0]|Elf32_Word|如果第0个符号查找不匹配，这里记录下一个可能匹配的符号索引|
|chain[1]|Elf32_Word|如果第1个符号查找不匹配，这里记录下一个可能匹配的符号索引|
|...|...|...|
|chain [s_symnum - 1]|Elf32_Word|如果第s_symnum - 1个符号查找不匹配，这里记录下一个可能匹配的符号索引|
|s_strtab|n字节|这里保存着一个字符串表，主要包含dso文件名和符号表的符号|

chain数组记录中，如果不存在下一个可能符号的符号，则这里应该存放UNDEF (0)

由于UNDEF定义为0，所以符号表中的第0个符号应该为NULL


符号名的Hash算法如下：
```
unsigned long
elf_hash(const unsigned char *name)
{
    unsigned long h = 0, g;
    while (*name)
    {
        h = (h << 4) + *name++;
        if (g = h & 0xf0000000)
            h ^= g >> 24;
        h &= ~g;
    }
    return h;
}
```


## PT_IMPREL
导入重定位信息表，用于程序依赖动态库的时候，在导入动态库中的函数与变量，解决符号重定位的信息表格。

导入重定位信息表组成结构如下：

|字段|大小|说明|
|--	|--	|--	|
|i_rev|Elf32_Addr/Elf64_Addr|保留|
|i_slotnum|Elf32_Word|需要导入重定位的符号个数，下面用N代表|
|i_dsonum|Elf32_Word|依赖的动态库个数，下面用M代表|
|i_dsoname[0]|Elf32_Addr/Elf64_Addr|第0个dso名字|
|...|...|...|
|i_dsoname [M - 1]|Elf32_Addr/Elf64_Addr|第M-1个dso名字|
|i_slotstart[0]|Elf32_Word|第0个dso首个slot在整个slot表的偏移|
|...|...|...|
|i_slotstart [M - 1]|Elf32_Word|第M-1个dso首个slot在整个slot表的偏移|
|i_slot[0]|Elf32_Addr/Elf64_Addr|第0个slot|
||||
|i_slot[N-1]|Elf32_Addr/Elf64_Addr|第N-1个slot|
|i_strtab|n字节|这里保存着一个字符串表，主要包含dso文件名和符号表的符号，第一个字节为'\0'|

这里的slot数组记录了所有需要导入的符号与重定位信息。
每一个需要依赖的dso动态库对应若干个slot，i_slotstart数组记录了每个dso对应的slot起始索引值。
每个dso动态库对应的slot列表都是以0作为结束标志。

slot的意义解释如下：
1. 当slot值为0时，表示结束标志。以下条件都是与slot不为0为前提条件。
2. 当slot值不为0时，表示为正常的slot序列串。每个slot为一个ADDR大小的整数，32位时为4字节，64位时为8字节。

基于以上slot值不为0的情况，可以分为：
1. 当最高位为1时，该slot与下一个slot组合在一起，2个slot合成的信息来描述一个导入重定位信息。
2. 当最高位为0时，该slot与下面2个slot组合在一起，3个slot合成的信息来描述一个导入重定位信息。

注意：当32位时，最高位为Bit-31；当64位时，最高位为Bit-63

2个slot合成的导入重定位信息描述如下：

|字段|大小|说明|
|--	|--	|--	|
|flag|最高位<br/>bit31 (32位时)<br/>bit63: (64位时)|标志，值为1|
|i_symname|bit0~bit30（32位时）<br/>bit0~bit62（64位时）|符号名的地址|
|i_addr|Elf32_Addr/Elf64_Addr|地址值。未解决符号装载之前，这里保存为数值(size_t)(-1)；装载器找到动态库中的符号之后，这里的值会被改写，装载器会把符号的地址值保存在这里|

3个slot合成的导入重定位信息描述如下：

|字段|大小|说明|
|--	|--	|--	|
|flag|最高位<br/>bit31 (32位时)<br/>bit63: (64位时)|标志，值为0|
|i_symname|bit0~bit30（32位时）<br/>bit0~bit62（64位时）|符号名的地址|
|i_offset|Elf32_Addr/Elf64_Addr|重定位偏移值。这里指出需要重定位的位置|
|i_info|Elf32_Addr/Elf64_Addr|重定位的额外信息<br/>bit3~bit0: 重定位类型 (从1开始枚举) <br/>其他bit：保留|

重定位类型:

|值|意思|
|--	|--	|
|0x01|重定位位置是一个绝对地址|
|0x02|重定位位置是32位相对偏移地址|




---





