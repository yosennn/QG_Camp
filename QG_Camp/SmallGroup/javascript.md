# JavaScript



# JavaScript实现

完整的 JavaScript 包括

1. 核心（ECMAScript）
2. 文档对象模型（DOM）
3. 浏览器对象模型（BOM）

## 1.ECMAScript

ECMA-262 定义的语言

## 2.DOM

## 3.BOM

---



# 编写位置

## 1.内部

写在`<script></script>`中，应该写在`<body>`上面

## 2.外部

见代码

```javascript
<script src="URL"></script>
```

注意

+ 内外均有 javascript 时，只执行外部
+ URL 也可以是链接

## 3.行内

见代码

```javascript
<button onclick="alert('Hello')"></button>
```

双引号内为 JavaScript 代码，且代码中的双引号变单引号

------

# 语言基础

## 1.语法

### 1.1.区分大小写

### 1.2.注释写法

与C语言相同

```javascript
//Hello
/*
Hello*/
```



### 1.3.标识符

### 1.4.语句

语句以分号结尾；也可以不加，由解析器来加

多条语句合并成一个由花括号包起来的代码块中

## 2.关键字和保留字

关键字有特殊作用，不能被用作标识符或属性名

保留字也不能被用，它们是保留给未来版本做关键字使用的

## 3.变量

ECMAScript 变量是松散类型的，意思是可以用于保存容易类型的数据

### 3.1. var 关键字

#### 1.var 声明作用域

由 var 定义的变量会成为包含它的函数的局部变量，退出函数时变量将被销毁

```javascript
var message = "Hello";
```



声明时去掉 var 可以创建一个全局变量，但不推荐这样操作

用逗号分隔可以一次声明多个变量

#### 2.var 声明提升

对于以下代码

```javascript
console.log(message);
var message;
```

不会报错且能正常运行，因为 ECMAScript 运行时等同于如下代码

```javascript
var message;
console.log(message);
```

这就是 提升（hoist），会把所有的变量声明拉到作用域的顶部

此外，我们还能反复用var声明同一个变量

```javascript
var age = 17;
var age = 18;
var age = 19;
```
### 3.2 let 声明

与 var 相比，let 的最大区别是其范围为块作用域，而 var 声明的范围是函数作用域

------

# 输入输出语句

## 1.输出语法

### document.write

向body内输出内容，如果输出内容写的是标签（如`<h1></h1>`），也会被解析为页面元素

```javascript
document.write("Hello");
```

### alert

弹出一个警示对话框

### console.log

控制台输出语法，常用于调试

## 2.输入语法

### prompt

显示一个对话框，包含一条文字信息，提示用户输入文字

```javascript
prompt("提示");
```
注：获得的数据为字符串

------



# 数组

## 声明

```javascript
let arr = [10,20,30];
let arr = ['rainy','During']
```

## 使用

与C语言类似，`数组名[数字]`能引用其中的一个数据，且从0开始计数

```javascript
console.log(arr[0]);
```

在 JavaScript 中，数组能存储任意类型的数据

## length 属性

`length`的值为其所含元素的数量

```javascript
let arr = ['rainy','During','xeyru']
console.log(arr.length);
```

此时输出的值为3

------



# 常量

使用`const`代替`let`声明一个不会改变的变量，与C语言中的常变量类似

声明是必须赋值，不允许重新赋值

------



# 数据类型

JavaScript 是一门弱数据类型的语言（C语言为强数据类型）

## 1.数字类型（number）

整数小数均可

## 2.字符串类型（string）

在JavaScript中，被\" 、\' 或\` 包住的数据被认为是字符串

### 2.1拼接

运算符`+`左右是字符串时可以实现字符串的拼接，也可以实现字符串和变量的拼接

```javascript
console.log("Hello, " + "I am" + name);
```

### 2.2模版字符串

用法如图

```javascript
console.log(`Hello, I am${name}`);
```

要求用反引号包起字符串，用`${}`包裹变量

## 3.布尔类型（boolean）

有两个固定的值 true 和 false

## 4.未定义类型（undefined）

不赋值的情况下，变量的值默认为 undefined

## 5.空类型（null）

JavaScript 中的`null`仅代表“空”，日后学对象时再用

与`undefined`相比，`null`其实赋值了，但是内容为空

## 6.检测数据类型

用`typrof`能检测变量的类型

其返回值为被检测的变量的数据类型，支持两种语法形式

1. 作为运算符`typeof aaa`
2. 函数形式`typeof(aaa)`

```javascript
let aaa = 11;
console.log(typeof aaa);
```

上述代码运行后输出number，表示变量`aaa`是数字类型

---

# 数据类型转换

## 1.隐式转换

某些运算符执行时，会自动将数据类型进行转换

规则

* 加号`+`两边有一边是字符串，另一边也变成字符串
* 但是`+`作为正号时可以把数据变成
* 除加号以外的字符串，比如`- * /`都会把数据转化为数字类型

## 2.显式转换

### 2.1. 转换为数字类型

#### 2.1.1. Number()

转换为数字，如果字符串内有非数字，则返回`NaN`（Not a Numebr）

`NaN`也是number类型的数据

#### 2.1.2. parselnt()

只保留整数，小数部分直接舍去（同C语言取整）

#### 2.1.3. parseFlaot()

可以保留小数 

#### 2.1.4. 特殊用法

两种 parse写法可以忽略数字后面的单位

```javascript
paeseInt("12px");
parseFloat("12.34px");
parseInt("abc12px");//返回NaN
```

前两行代码都能忽略后面的字母返回数字，但是如果数字部分在字母中间则会返回`NaN`

因为 CSS 中常见14px这样的数值，这样的特性在联动时更加方便

---

# 运算符

## 1.赋值运算符

等号`=`用法同C语言，同时也有`+= -= *= /= %=`操作

## 2.一元运算符

自增`++`，自减`--`，也分前置和后置。前置先加一再运算，后置则反之

## 3.比较运算符

有`> < >= <= == === !==`，返回值为boolean类型，即 true 或 false

其中前四个与 C语言类似

### 3.1. 双等号 ==

双等号`==`是判断，只判断数值是否相等，使用时可能会发生隐式转换，如

```javascript
2 == "2";
```

上式的值为true

### 3.2. 三等号 ===

三等号`===`是全等，要求类型和数值都相等

开发中推荐使用三等

### 3.3. 字符串比较

同C语言中 strcmp 函数

### 3.4. NaN 不等于任何值

如题

---

# 逻辑运算符

即`&& || !`，用法同 C语言

---

# 语句

## 1.表达式和语句

表达式是可以被求值的代码，可用作赋值

语句是可被执行的代码，不一定有值

## 2.分支语句

### 2.1. if语句

同C语言，也可以加大括号塞一堆语句

非零数字、非空字符串和 true 均为真，执行语句

```javascript
if(condition)
	...;
else
    ...;
```

还有`else if`写法同C

### 2.2. 三元运算符

同C语言

```javascript
condition?yes:no;
```

### 2.3. switch 语句

类似C语言

```javascript
switch(变量) {
    case 数值:
        ...;
        break;
    default:
        ...;
}
```

case 后面的数值是按照全等`===`来判断的

## 3.循环语句

### 3.1. while循环

用法同C语言

```javascript
while (i < 10){
    ...;
}
```

### 3.2. 退出循环

同C语言，`break`跳出循环，`continue`跳过本次循环

### 3.2. for循环

同C语言

```javascript
for(let i = 0;i < 3;i++){
    ...;
}
```





# 断点

在浏览器开发者模式里设置断点
