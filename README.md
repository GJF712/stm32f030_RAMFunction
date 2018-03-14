# stm32f030_RAMFunction
keil+stm32将函数放置到RAM执行，两种方法

第一种方法，就是copy到数组，有很多种方法，但是要注意是从奇数地址开始

第二种方法，在keil平台有一个更简便的方案（将函数放到RAM中执行）：
首先备份工程，再为要指定的函数定义一个section名字（如 void FunctionName(void) __attribute__((section("SectionName")));，
前一个Name与函数有关，后一个Name为section名字(自定义)）。
然后在工程设置里面，点击Linker选项卡，第一步去掉Use Memory Layout from Target Dialog选项，
第二步，点击Scatter File后面的Edit选项（此时工程会打开一个.sct的文件），再点击OK（关闭工程设置窗口，一定不要忘记点击OK）。
最后在.sct文件中RAM区域加上一行“* （SectionName）”（section名字）。保存重新编译即可。参考设置如下：

LR_IROM1 0x08000000 0x00004000 { ; load region size_region
  ER_IROM1 0x08000000 0x00004000 { ; load address = execution address
    *.o (RESET, +First)
    *(InRoot$$Sections)
    .ANY (+RO)
  }
  RW_IRAM1 0x20000000 0x00001000 { ; RW data
    .ANY (+RW +ZI)
    * (SectionName)
  }
}
