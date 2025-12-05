#!/bin/bash
# 检查参数是否缺失
# $# 变量会自动存储用户输入了多少个参数（比如 './script dir --dry-run' 就是 2 个参数）
if [ "$#" -lt 1 ]; then
    echo "错误：请提供目标目录路径作为第一个参数。"
    echo "用法：./organize_files.sh <目标目录> [--dry-run]"
    exit 1 # exit 1 代表脚本运行失败，需要停止
fi

# 如果通过了上一步检查，我们就可以确定第一个参数 $1 是目标目录
TARGET_DIR="$1"
# 检查目录是否存在
# -d 检查后面跟着的 TARGET_DIR 是不是一个目录（文件夹）
# ! 符号代表“不是”
if [ ! -d "$TARGET_DIR" ]; then
    echo "错误：目录 '$TARGET_DIR' 不存在或不是一个有效的目录。"
    exit 1
fi
DRY_RUN=false # 默认关闭模拟运行模式

# 检查用户是否输入了第二个参数 ($2)，并且第二个参数是不是 "--dry-run"
if [ "$#" -gt 1 ] && [ "$2" == "--dry-run" ]; then
    DRY_RUN=true
    echo "========================================"
    echo "【模拟运行模式】已开启：不会移动任何文件。"
    echo "========================================"
fi

# 脚本主体运行的开始提示
echo "正在开始整理目录：$TARGET_DIR"
# 步骤 4.1：设置日志文件路径
LOG_FILE="$TARGET_DIR/organizer_log.txt"

# 清空或创建日志文件，并写入开始时间
echo "### File Organization Log - $(date +%Y-%m-%d\ %H:%M:%S) ###" > "$LOG_FILE"
echo "" >> "$LOG_FILE"

echo "日志文件已创建/清空：$LOG_FILE"


# 步骤 4.2：遍历文件
# find 命令查找目标目录下的所有文件 (-type f)
find "$TARGET_DIR" -type f -print0 | while IFS= read -r -d $'\0' file; do

    # 跳过日志文件本身，防止脚本尝试移动它
    if [[ "$file" == "$LOG_FILE" ]]; then
        continue
    fi

    # 4.2.1: 提取文件名和扩展名
    FILENAME=$(basename "$file") 

    # ${FILENAME##*.}：提取扩展名
    EXTENSION="${FILENAME##*.}"

    # 转换为小写，保证目录名统一
    LOWER_EXTENSION=$(echo "$EXTENSION" | tr '[:upper:]' '[:lower:]')

    # 4.2.2: 确定目标路径
    DEST_DIR="$TARGET_DIR/$LOWER_EXTENSION" 
    DEST_PATH="$DEST_DIR/$FILENAME"         


    # 4.2.3: 打印操作信息（Dry-Run/实际操作）
    if $DRY_RUN; then
        # DRY-RUN 模式只打印信息
        echo "[DRY-RUN] Would move '$FILENAME' to '$DEST_PATH'"
    else
        # 实际移动模式
        echo "[ACTION] Moving '$FILENAME' to '$DEST_PATH'"

        # -p 选项：创建目标目录
        mkdir -p "$DEST_DIR"

        # 移动文件：mv [原路径] [新路径]
        mv "$file" "$DEST_PATH"

        # 4.2.4: 记录日志
        echo "$(date +%Y-%m-%d\ %H:%M:%S) | Moved | $file -> $DEST_PATH" >> "$LOG_FILE"
    fi

done

echo ""
echo "整理完成！请查看目录 '$TARGET_DIR' 和日志文件 '$LOG_FILE'。"
