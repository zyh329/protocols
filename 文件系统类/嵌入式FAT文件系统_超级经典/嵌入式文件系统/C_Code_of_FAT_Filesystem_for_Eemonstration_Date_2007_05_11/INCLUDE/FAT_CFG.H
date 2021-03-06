/*
+FHDR------------------------------------------------------------------
Copyright (c),
Tony Yang –51,AVR,ARM firmware developer  
Contact:qq 292942278  e-mail:tony_yang123@sina.com.cn

Abstract:
$Id: fat_cfg.h,v 1.10 2007/03/31 14:25:42 design Exp $
-FHDR-------------------------------------------------------------------
*/
 #define FILE_NAME 0xff
 #define FILE_EXTENSION 0xfe  
 #define OK 0
 #define unOK 0xff

 //File attributes
 #define ATTR_READ_ONLY (1 << 0)
 #define ATTR_HIDDEN    (1 << 1)
 #define ATTR_SYSTEM    (1 << 2)
 #define ATTR_VOLUME_ID (1 << 3)
 #define ATTR_DIRECTORY (1 << 4)
 #define ATTR_ARCHIVE   (1 << 5)
 #define ATTR_LONG_NAME (ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID)
 //
 #define Last_LFN_Record (1 << 6) 
 //Partition Type ----0C-FAT32,06-FAT16 ect..
 #define FAT32 0xc
 #define FAT16 0x6
 //Directory Type
  //Maximum FullPath chars -In compliance with Microsoft Longfilename Specification
 #define Maximum_File_Path_Name 260
 //FAT Error Code Definitions As Following  
 //fseek origin
 #define SEEK_SET 0
 #define SEEK_CUR 1
 #define SEEK_END 2
 //
 #define EpathLengthsOVERFLOW 0xfa
 #define EAllocate_FCB 0xff
 #define EFree_FCB 0xfe
 #define Folder_Enumeration_Complete 1
 #define Create_File_Failed  2
 #define Create_Folder_Failed 3
 #define Rename_Of_File_Failed 4
 #define Open_File_Failed 5
 #define Open_Folder_Failed 6
 #define Read_File_Failed 7
 #define Write_File_Failed 8
 #define Delete_File_Failed 9
 #define Delete_Folder_Failed 10 
 #define Inquiry_Volume_Failed 11
 #define Autoformat_FAT_Filesystem_Failed 12
 #define  Invalid_PATH_Name 0xff
 #define  File_Extension_Over_limited_3_Char 0xfe
 #define  Invalid_chars_Found_In_File_Path  0xfd
 #define  File_Not_Found 0xfc 
 #define  LastSplitedNameofPath 0xfd
 //File opened flag
#define FileAlreadyopenedByOtherHandle 0
#define FileUnopenedByOtherHandle  0xff
//GetEntryFromDirectory mode
#define Get_Selected_ENTRIES 0 
#define Get_All_Entries 1
//Definition of FAT filesystem CORE Struct
struct core_{
  u8 current_folder[Maximum_File_Path_Name];//保存当前目录--只有cd_folder()能改变当前目录
                                            //系统重启后，默认当前目录为"C:\"
  u32 ClusterNOofCurrentFolder;//保存目录目录项所在ClusterNO
  u8 CurrentDirectoryType; //RootDirectory,NomeRootDirectory
  u8 PartitionID; //当前BPB中对应的PartitionID
  u8 system_id; //Partition type:0C-FAT32,06-FAT16 ect..
  u32 relative_sector; //Begining sector address of Current Partition
  u32 total_sector;   //Total sectors of Current Partition
  u32 FirstDataSector; ////The start of the data region, the first sector of cluster 2
  u32 FirstSectorofFAT1;
  u32 FirstSectorofFAT2;
  u16 FirstRootDirSecNum;  
  u16 RootDirSectors; //the count of sectors occupied by the root directory
  u16 CountofClusters; //count of clusters
  u32 DataSec;  //we determine the count of sectors in the data region of the volume
  //Public variables for path resolution
  u32 ClusterNum;   //存放当前Enumerated Directory Entry所在Directory的ClusterNum,SectorNum,offset
  u32 SectorNum;
  u16 offset;
  u32 ClusterOfDirectoryEntry;  //存放Directory Entry32字节中对应first Cluster Num
  u32 FileSize;
  u8 DirectoryType; 
  u8 FullPathType;
  u8 CurPathType; 
  //Variables for storage of pre-entry position
  u32 PreEntrySectorNum;
  u16 PreEntryoffset;
  //Variables for folder enumeration
  u32 DIR_ENUM_ClusterNum;   //存放当前Enumerated Directory Entry所在Directory的ClusterNum,SectorNum,offset
  u32 DIR_ENUM_SectorNum;
  u16 DIR_ENUM_offset;
  u32 DIR_ENUM_ClusterOfDirectoryEntry;  //存放Directory Entry32字节中对应first Cluster Num
  u8 DIR_ENUM_DirectoryType; 
  u8 DIR_ENUM_FullPathType;
  u8 DIR_ENUM_CurPathType; 
  u8 Entry_Attr;
};

 #define RootDirectory 0x0   //当前目录类型为RootDirectory，
                             //RootDirectory是存放于一片连续的固定扇区
 #define NoneRootDirectory 0x1 //NoneRootDirectory是存放于簇链来串接的scatterr region
 //Path Type
 #define DirectoryPath 0x10  //比如CD命令使用的路径Type:DirectoryPath
 #define FilePath 0x3       //比如open命令使用的路径Type:FilePath,即路径的最后是文件名 
 //Definition of FileBufSize for FileRead/Write
 #define EnableFileBuf 1  
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#if EnableFileBuf
   #define TotalFileBUFsQTYeachFCB 64 //TotalFileBUFsQTY for each FCB 
#else 
   #define TotalFileBUFsQTYeachFCB 0 //TotalFileBUFsQTY for each FCB 
#endif
 #define FileBUFSize 512 //This is a fixed size,!!!Pls don't change!!! 
 #define MaximumFCB 10     //which means 4 files can be opened at the same time
 #define UnusedFlag 0x0
 #define UsedFlag 0x1 
//Read File Optimization Selector--选择Read File实现的两种方法之一
//0--需要代码少
//1--对缓冲区依赖明显
#define Read_File_Optimization_Selector 1
//Write File Optimization Selector--选择Write File实现的两种方法之一
//0--需要代码少
//1--对缓冲区依赖明显
#define Write_File_Optimization_Selector 1

 //Permission
 #define FullPermission 0
 #define ReadOnlyPermission 1  
//FCB Struct   
struct FileControlBlock{
  //Public variables and FileBlockBUF for fileRead/Write
  u8 file_openned_flag;
  u32 CurBlockInBUF; 
 #if EnableFileBuf
  u8 FileBUF[FileBUFSize * TotalFileBUFsQTYeachFCB]; 
 #endif                                              
  u32 FileSize;
  u32 cur_position;
  u32 FirstClusterOfFile; 
  u8  Permission;
  u8  Modified_Flag;
  u32 Entry_Storedin_Sector;  //Storage sectorNUM of File Directory entry 
  u16 Entry_Storedin_Sector_Offset; //Storage of offset in sector of File Directory entry
}; 
//处理时间动作定义宏
//0-不处理，其它-处理
#define enable_time_transaction 0

//Definition of BPB Struct
struct partition_bpb{
  u16 bytes_per_sector;//每扇区字节数
  u8 sector_per_cluster; //每簇扇区数
  u16 reserved_sector;  //保留扇区数
  u8 numbers_of_FAT;//FAT副本数
  u16 boot_entries;//根目录项数，供FAT12/16使用
  u16 TotSec16; //This field is the old 16-bit total count of sectors on the volume.
  u8 media_descriptor; //媒体描述符
  u16 sectors_per_FAT; //每个FAT表占用的扇区数，供FAT12/16使用
  u16 sectors_per_track; //每道扇区数
  u16 number_of_head; //磁头数
  u32 BPB_HiddSec; //隐藏扇区数
  u32 BPB_TotSec32;//总扇区数，包含FAT32总扇区数
  u8 BS_DrvNum;
  u8 BS_Reserved1;
  u8 BS_BootSig;
  u32 BS_VolID;
  u8 BS_VolLab[11];
  u8 BS_FilSysType[8];
};

//Definition of Directory Entry Struct
struct Directory_Entry_{
  u8 filename[8];//文件名
  u8 file_extention[3]; //文件扩展名
  u8 file_attribute;//属性
  u8 reserved;
  u8 create_time_10ms;//创建时间的10毫秒位
  u8 file_created_time[2];//文件创建时间
  u8 file_created_date[2];//文件创建日期
  u8 last_access_date[2];//文件最后访问日期
  u8 first_cluster_number_high2bytes[2]; //文件首簇号高16位
  u8 recent_modified_time[2];//文件最近修改时间
  u8 recent_modified_data[2];//文件最近修改日期
  u8 first_cluster_number_low2bytes[2]; //文件首簇号低16位
  u8 file_length[4];//文件长度
};

//Long Name Directory Entry
struct LongNameDirectoryEntry{
u8 dir_lname1[10];//long name string
u8 dir_sig;   // signature byte
u8 dir_attr;   // file attributes
u8 dir_flags;   //flags byte (TBD)
u8 dir_chksum; //checksum of 8.3 name
u8 dir_lname2[12];// long name string
u8 dir_first[2];     //first cluster number, must be 0
u8 dir_lname3[4]; //long name string
};
// disk enumeration configuration
#define filter_hidden_entry 0
//compile functions of FAT filesystem ?
#define complie_create_file 1
#define complie_create_floder 1 
#define complie_open_file 1
#define complie_close_file 1
#define complie_rename_file 1
#define complie_folder_dir 1 
#define compile_fseek 1
#define complie_read_file 1
#define complie_write_file 1
#define compile_cd_folder 1
#define complie_delete_file 1
#define complie_delete_folder 1
#define complie_volume_inquiry 1
#define complie_find_file 1
#define complie_FAT_filesystem_initialiation 1
#define complie_FAT16_filesystem_autoformat 0 



/*
+FFTR--------------------------------------------------------------------
$Log: fat_cfg.h,v $
Revision 1.10  2007/03/31 14:25:42  design
给read_file(),write_file()增加一种优化的实现方法
对应fat_cfg.h增加两个编绎宏
#define Read_File_Optimization_Selector 1
#define Write_File_Optimization_Selector 1

Revision 1.9  2007/03/25 03:42:16  design
create_file(),create_folder(),rename_file()测试通过
create_file(),create_folder()测试方法如下：
在目录test,ok下分别建500个文件，目录，之后用disk_enumeration分
离成功
rename_file()测试方法如下：
将文件"C:\TEST.PDF"改名为"DFDFDFDFDFDFDFDFSDFSDTONY.TXT"成功

Revision 1.8  2007/03/17 03:10:03  design
write_file测试成功
测试方法：
写3m rar文件，再读出，解压通过

Revision 1.7  2007/03/11 10:23:51  yangwenbin
disk_enumeration,folder_enumeration函数测试成功
测试方法:
分离大小为127M IMG的所含文件，如rar,pdf等

Revision 1.6  2007/03/06 14:49:05  yangwenbin
cd_folder()函数测试成功

Revision 1.5  2007/03/06 12:26:56  yangwenbin
函数cd_folder()完成， mode 0/mode1两种模式测试通过

Revision 1.4  2007/03/04 03:01:00  yangwenbin
open_file(),f_seek(),read_file(),
文件：C:\longfilename directory for test\tony yang and\test_test.txt
测试成功

Revision 1.3  2007/03/03 15:39:52  yangwenbin
open_file,f_seek,read_file
读1.9M文件测试成功

Revision 1.2  2007/02/28 13:39:51  Design
函数open_file打开绝对路径+短文件名测试通过
使用C代码如下：
open_file("C:\\HELLO.TXT")

Revision 1.1.1.1  2007/02/26 14:01:12  Design
volume_inquire函数测试成功

Revision 1.1.1.1  2007/02/24 07:59:45  yangwenbin
增加FAT16文件系统基本代码

-FFTR--------------------------------------------------------------------
*/