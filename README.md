# 第三方库安装和使用

## 第三方库介绍
已安装的库：absl、gflags、glog、gmock、protobuf、gtest
头文件：/usr/local/include
连接库：/usr/local/lib

## 一、Gtest 入门

### 1.1 单元测试
单元测试其实就是对模块、类、函数实现的功能执行检测，看看是否满足预期，是否达到功能要求，它是一次检查检验的过程。如果某个模块或者函数满足预期，则表示测试通过，否则表示失败，比如工厂在组装一台电视机之前，会对每个元件都进行测试看是否合格，这就是单元测试，是不是很好理解。

### 1.2 测试的规则
那么什么才是好的测试，googletest 又是如何适应的呢？
1. **测试应该是独立的和可重复的：** 调试由于其他测试而成功或失败的测试是一件痛苦的事情。googletest 通过在不同的对象上运行每个测试来隔离测试。当测试失败时，googletest 允许您隔离运行它以进行快速调试。
2. **测试应该组织良好并反映被测代码的结构：** googletest 将相关测试分组为可以共享数据和子程序的测试套件。这种常见模式很容易识别并使测试易于维护。当人们切换项目并开始使用新的代码库时，这种一致性特别有用。
3. **测试应该是可移植和可重用的：** 谷歌有很多平台中立的代码；它的测试也应该是平台中立的。googletest 适用于不同的操作系统，使用不同的编译器，有或没有例外，因此 googletest 测试可以使用各种配置。
4. **当测试失败时，他们应该提供尽可能多的关于问题的信息：** googletest 不会在第一次测试失败时停止。相反，它只会停止当前测试并继续下一个测试。您还可以设置报告非致命故障的测试，然后继续当前测试。因此，您可以在单个运行-编辑-编译周期中检测并修复多个错误。
5. **测试框架应该将测试编写者从家务活中解放出来，让他们专注于测试内容：** googletest 自动跟踪所有定义的测试，并且不需要用户枚举它们来运行它们。
6. **测试应该很快：** 使用 googletest，您可以跨测试重用共享资源，并且只需为设置/拆卸支付一次费用，而无需使测试相互依赖。

### 1.2 断言

1. ASSERT_*
如果在相关断言失败时继续没有意义

2. EXPECT_*
生成非致命故障，不会中止当前功能

例子：
``` c++
TEST(ClassMath, add) {
  // 出错不中断
  EXPECT_EQ(add(1 + 1), 1 + 1);
  // 出错中断
  ASSERT_EQ(add(1 + 1), 1 + 3);
}

```

### 1.3 复杂的测试

如果您发现自己正在编写两个或多个对相似数据进行操作的测试，则可以使用**Test Fixtures**。这允许您为多个不同的测试重用相同的对象配置。

1. 从 ::testing::Test 派生一个类。它的主体以 protected: 开始，因为我们想要从子类访问夹具成员。
2. 在类中，声明您计划使用的任何对象。
3. 如有必要，编写默认构造函数或SetUp()函数来为每个测试准备对象。一个常见的错误是拼写SetUp()为 Setup()小写u-override在 C++11 中使用以确保拼写正确。
4. 如有必要，编写一个析构函数或TearDown()函数来释放您在SetUp(). 要了解何时应使用构造函数/析构函数以及何时应使用SetUp()/TearDown()，请阅读常见问题解答。
5. 如果需要，为您的测试定义子例程以共享。

例子：
``` C++
class QueueTest : public ::testing::Test {
 protected:
// 重写 SetUp() 初始化和 TearDown() 清除资源
  void SetUp() override {
     // q0_ remains empty
     q1_.Enqueue(1);
     q2_.Enqueue(2);
     q2_.Enqueue(3);
  }

  // void TearDown() override {}

  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};


TEST_F(QueueTest, IsEmptyInitially) {
  EXPECT_EQ(q0_.size(), 0);
}

```

### 1.3 调用测试

RUN_ALL_TESTS()
执行步骤：
1. 保存所有 googletest 标志的状态。
2. 为第一个测试创建一个测试夹具对象。
3. 通过初始化它SetUp()。
4. 在夹具对象上运行测试。
5. 通过 清理夹具TearDown()。
6. 删除夹具。
7. 恢复所有 googletest 标志的状态。
8. 对下一个测试重复上述步骤，直到所有测试都运行完毕。

main()函数必须返回 RUN_ALL_TESTS() 的返回值；只调用一次，多次调用它会与某些高级 googletest 功能（例如，线程安全的 死亡测试）发生冲突。

不提供 main 函数需要编译时添加链接库 -lgtest_main。

## 2. 高级主题

### 2.1 返回断言结果的函数

对象表示断言的结果（无论它是 成功或失败，以及关联的消息）。

``` c++
namespace testing {
  AssertionResult AssertionSuccess();
  AssertionResult AssertionFailure();
}

```

返回结果并打印日志结果

``` c++
testing::AssertionResult IsEven(int n) {
  if ((n % 2) == 0)
    // 有返回的
    return testing::AssertionSuccess();
  else
    // 返回值直接打印日志
    return testing::AssertionFailure() << n << " is odd";
}

// 对比 直接返回 bool 值
bool IsEven(int n) {
  return (n % 2) == 0;
}

// 方式 1 的结果，打印日志更详细丰富
Value of: IsEven(Fib(4))
  Actual: false (3 is odd)  // 打印日志
Expected: true

// 方式2 的结果
Value of: IsEven(Fib(4))
  Actual: false
Expected: true

```

