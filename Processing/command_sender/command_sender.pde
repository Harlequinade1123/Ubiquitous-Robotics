import controlP5.*;
import jp.go.aist.rtm.OpenRTMUtil;
import jp.go.aist.rtm.RTC.port.InPort;
import jp.go.aist.rtm.RTC.port.OutPort;
import jp.go.aist.rtm.RTC.util.DataRef;
import RTC.TimedLong;
import RTC.Time;

ControlP5 button;

//データ、InPortの変数を宣言
DataRef<TimedLong> indata;
InPort<TimedLong>  inport;

//データ、InPortの変数を宣言
DataRef<TimedLong> outdata;
OutPort<TimedLong> outport;

boolean isFetching  = false;
boolean isReturning = false;
boolean isCanceled  = false;

int g_command = 0;
int g_button_num = 2;
int g_select_button_width = 150;
String[] g_button_names = 
{
    "Please select the tool.",
    "SCREW",
    "WRENCH",
    "SCREWDRIVER"
};
int g_progress = 0;


OpenRTMUtil util  = new OpenRTMUtil();
TimedLong in_val  = new TimedLong();
TimedLong out_val = new TimedLong();

public void setup()
{
    //ウィンドウサイズを設定
    size(800, 600);

    util.createComponent("CommandSender");
    
    //データの初期化
    out_val.tm   = new Time();
    out_val.data = 0;
    outdata      = new DataRef<TimedLong>(out_val);
    outport      = util.addOutPort("command", outdata);
    
    // 何故か outport と併用できないので現在保留
    // in_val.tm   = new Time();
    // in_val.data = 0;
    // indata      = new DataRef<TimedLong>(in_val);
    // inport      = util.addInPort("state", indata);

    frameRate(100); //frame rate 100Hz
    smooth(); //anti-aliasing

    PFont myFont    = createFont(PFont.list()[100], 16, true);
    ControlFont cf1 = new ControlFont(myFont, 14);
    button          = new ControlP5(this);

    for (int button_i = 0; button_i < g_button_num; button_i++)
    {
        button.addButton(g_button_names[button_i + 1])
            .setLabel(g_button_names[button_i + 1])
            .setFont(cf1)
            .setPosition(width / (g_button_num + 1) * (button_i + 1) - g_select_button_width / 2, height/2)
            .setSize(g_select_button_width, 50)
            .setColorActive(color(100, 150, 150))
            .setColorBackground(color(50, 150, 50))
            .setColorForeground(color(100, 150, 100))
            .setColorCaptionLabel(color(255, 255, 255));
    }

    // ツール回収コマンド
    button.addButton("FETCH")
        .setLabel("FETCH")
        .setFont(cf1)
        .setPosition(width / 2 - 200, height / 2 + 100)
        .setSize(400, 50)
        .setColorActive(color(100, 120, 150))
        .setColorBackground(color(50, 50, 150))
        .setColorForeground(color(100, 100, 150))
        .setColorCaptionLabel(color(255, 255, 255));

    // キャンセルコマンド（間に合ったら）
    // button.addButton("CANCEL")
    //     .setLabel("CANCEL")
    //     .setFont(cf1)
    //     .setPosition(width / 2 - 200, height / 2 + 160)
    //     .setSize(400, 50)
    //     .setColorActive(color(100, 120, 150))
    //     .setColorBackground(color(50, 50, 150))
    //     .setColorForeground(color(100, 100, 150))
    //     .setColorCaptionLabel(color(255, 255, 255));

    // ツール返却コマンド
    button.addButton("RETURN")
        .setLabel("RETURN")
        .setFont(cf1)
        .setPosition(width / 2 - 200, height / 2 + 220)
        .setSize(400, 50)
        .setColorActive(color(100, 120, 150))
        .setColorBackground(color(50, 50, 150))
        .setColorForeground(color(100, 100, 150))
        .setColorCaptionLabel(color(255, 255, 255));

    button.addToggle("mode_is_manual")
        .setColorLabel(color(0))
        .setLabel("MANUAL")
        .setFont(cf1)
        .setPosition(80,310)
        .setSize(50,20)
        .setValue(false);
}
boolean mode_is_manual = false;
public void draw()
{
    background(255);
    fill(0);
    textAlign(CENTER);
    textSize(72);
    if (!mode_is_manual)
    {
        text(g_button_names[g_command], width / 2, 120);
    }
    else
    {
        text("↑↓←→:MOVE", width / 2, 100);
        text("Z or X:TURN"     , width / 2, 160);
        text("F    :FETCH"      , width / 2 + 55, 220);
        text("R    :RETURN"     , width / 2 + 78, 280);
        isFetching  = false;
        isReturning = false;
        isCanceled  = false;
        g_progress = 0;

        out_val.data = 100;
        if (keyPressed)
        {
            if (keyCode == UP)
            {
                out_val.data = 101;
            }
            else if (keyCode == DOWN)
            {
                out_val.data = 102;
            }
            else if (keyCode == LEFT)
            {
                out_val.data = 103;
            }
            else if (keyCode == RIGHT)
            {
                out_val.data = 104;
            }
            else if (key == 'z' || key == 'Z')
            {
                out_val.data = 105;
            }
            else if (key == 'x' || key == 'X')
            {
                out_val.data = 106;
            }
            else if (key == 'f' || key == 'F')
            {
                out_val.data = 107;
            }
            else if (key == 'r' || key == 'R')
            {
                out_val.data = 108;
            }
        }
        out_val.tm = new Time();
        outport.write();
        println("MANUAL:", out_val.data);
        if (keyPressed && (key == 'r' || key == 'R' || key == 'f' || key == 'F'))
        {
            delay(20000);
        }
        delay(100);
    }
    if (!mode_is_manual && (isFetching || isReturning))
    {
        textSize(24);
        if (100 <= g_progress)
        {
            text("Task is finished!", width / 2, 180);
        }
        else if (g_progress <= 0)
        {
            text("Task is canceled!", width / 2, 180);
        }
        else if (isCanceled)
        {
            text("Now Canceling...", width / 2, 180);
        }
        else if (isFetching)
        {
            text("Now Fetching...", width / 2, 180);
        }
        else if (isReturning)
        {
            text("Now Returning...", width / 2, 180);
        }
        rectMode(CENTER);
        stroke(0);
        strokeWeight(1);
        fill(255);
        rect(width / 2, 240, 2 * width / 3, 50);
        noStroke();
        fill(0, 200, 220);
        for (int i = 0; i < g_progress; i++)
        {
            rect(width / 2 - 2 * width / 3 / 2 + 5 + i * 2 * width / 3 / 101, 240, 2 * width / 3 / 101, 45);
        }
        if (101 <= g_progress)
        {
            delay(2000);
            isFetching  = false;
            isReturning = false;
            isCanceled  = false;
            g_progress = 0;
        }
        else if (g_progress <= -1 && isCanceled)
        {
            delay(2000);
            isFetching  = false;
            isReturning = false;
            isCanceled  = false;
            g_progress = 0;
        }
        if (!isCanceled)
        {
            g_progress++;
        }
        else
        {
            g_progress--;
        }

        //タスクを終えるまでの時間に合わせて修正
        //delay((20000 + 9000)/100);
    }
}

void SCREW()
{
    if (!mode_is_manual && !isFetching && !isReturning)
        g_command = 1;
}

void WRENCH()
{
    if (!mode_is_manual && !isFetching && !isReturning)
        g_command = 2;
}

void SCREWDRIVER()
{
    if (!mode_is_manual && !isFetching && !isReturning)
        g_command = 3;
}

void FETCH()
{
    if (!mode_is_manual && 0 < g_command && !isFetching && !isReturning)
    {
        out_val.tm = new Time();
        out_val.data = g_command;
        outport.write();
        println("FETCH:", g_command);
        isFetching = true;
    }
}

void CANCEL()
{
    if (!mode_is_manual && (isFetching || isReturning))
    {
        isCanceled = true;
        out_val.tm = new Time();
        out_val.data = -1;
        outport.write();
        println("CANCEL");
    }
}

void RETURN()
{
    if (!mode_is_manual && 0 < g_command && !isFetching && !isReturning)
    {
        out_val.tm = new Time();
        out_val.data = g_command * 10;
        outport.write();
        println("RETURN:", g_command);
        isReturning = true;
    }
}
