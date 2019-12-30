# virtial-machine
## Example source code
```java
public class Main {
    public static void main(String args[]) {
        int arg1 = 1;
        int arg2 = 2;
        System.out.println(arg1+arg2);
    }
}
```

```
public class Main {
  public <init>()V
   L0
    LINENUMBER 1 L0
    ALOAD 0
    INVOKESPECIAL java/lang/Object.<init> ()V
    RETURN
   L1
    LOCALVARIABLE this LMain; L0 L1 0
    MAXSTACK = 1
    MAXLOCALS = 1

  public static main([Ljava/lang/String;)V
   L0
    LINENUMBER 3 L0
    ICONST_1
    ISTORE 1
   L1
    LINENUMBER 4 L1
    ICONST_2
    ISTORE 2
   L2
    LINENUMBER 5 L2
    GETSTATIC java/lang/System.out : Ljava/io/PrintStream;
    ILOAD 1
    ILOAD 2
    IADD
    INVOKEVIRTUAL java/io/PrintStream.println (I)V
   L3
    LINENUMBER 6 L3
    RETURN
   L4
    LOCALVARIABLE args [Ljava/lang/String; L0 L4 0
    LOCALVARIABLE arg1 I L1 L4 1
    LOCALVARIABLE arg2 I L2 L4 2
    MAXSTACK = 3
    MAXLOCALS = 3
}
```