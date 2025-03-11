google.charts.load("current", {packages:["sankey"]});
google.charts.setOnLoadCallback(drawChart);

function drawChart() {
    /*讀取CSV檔案*/
    $.get("jsdata.csv", function(csvString) {
        // fetch CSV file using ajax
        var arrayData = $.csv.toArrays(csvString, {onParseValue: $.csv.hooks.castToScalar});
        // after parsing , arrayData is 2-D array holding all the data contained in CSV file
        var data = new google.visualization.DataTable();

        /*定義每個column的身分*/ 
        data.addColumn('string', 'From');
        data.addColumn('string', 'To');
        data.addColumn('number', 'Weight');
        data.addColumn({
            type: 'string',
            role: 'style',
        });
        data.addColumn({type: 'string', role: 'tooltip'});

        data.addColumn({type:'string', label:'X1axis1', role:'data'});
        data.addColumn({type:'string', label:'Y1axis_Max1', role:'data'});
        data.addColumn({type:'string', label:'Y1axis_min1', role:'data'});
        data.addColumn({type:'string', label:'X1axis2', role:'data'});
        data.addColumn({type:'string', label:'Y1axis_Max2', role:'data'});
        data.addColumn({type:'string', label:'Y1axis_min2', role:'data'});

        data.addColumn({type:'string', label:'X2axis1', role:'data'});
        data.addColumn({type:'string', label:'Y2axis_Max1', role:'data'});
        data.addColumn({type:'string', label:'Y2axis_min1', role:'data'});
        data.addColumn({type:'string', label:'X2axis2', role:'data'});
        data.addColumn({type:'string', label:'Y2axis_Max2', role:'data'});
        data.addColumn({type:'string', label:'Y2axis_min2', role:'data'});

        data.addColumn('string', 'protocal1');
        data.addColumn('string', 'protocal2');

        data.addRows(arrayData); /*將資料導入*/ 




        // Sets chart options.
        var options = {
            width: 600,
            tooltip:{isHtml: true},
            sankey: {
                link: {
                    color: { stroke: 'black', strokeWidth: 0 },
                    interactivity: true, /*開啟圖表互動功能*/
                },
                node: {
                    /*sankey的版面設定*/
                    width: 10,
                    labelPadding: 5,
                    label: { fontName: 'Times-Roman',
                        fontSize: 14,
                        color: '#871b47',
                        bold: true,
                        italic: true,
                    } } },




        };





        // Instantiate and draw our chart, passing in some options.
        var chart = new google.visualization.Sankey(document.getElementById('sankey_multiple'));
        chart.draw(data, options);
        
        google.visualization.events.addListener(chart, 'select', selectHandler);
        function selectHandler() {
            var selections = chart.getSelection(); /* selction為圖表指定的選項 */
            if (selections.length == 0) { /* 若重複點擊，重新整理 */
                location.reload();
            } else {
                var selection = selections[0]; 
                /* 針對第幾筆資料進行資料的抓取 */
                 const block1 = [{Xaxis: (data.getValue(selection.row, 5)),
                    Yaxis_Max:(data.getValue(selection.row, 6)),
                    Yaxis_min:(data.getValue(selection.row, 7))},
                    {Xaxis:(data.getValue(selection.row, 8)),
                        Yaxis_Max:(data.getValue(selection.row, 9)),
                        Yaxis_min:(data.getValue(selection.row, 10))}]
                mappedToArray1 = block1.map(d => Array.from(Object.values(d))); /* 將資料存進陣列之中 */

                /* 針對第幾筆資料進行資料的抓取 */
                const block2 = [{Xaxis:(data.getValue(selection.row, 11)),
                    Yaxis_Max:(data.getValue(selection.row, 12)),
                    Yaxis_min:(data.getValue(selection.row, 13))},
                    {Xaxis:(data.getValue(selection.row, 14)),
                        Yaxis_Max:(data.getValue(selection.row, 15)),
                        Yaxis_min:(data.getValue(selection.row, 16))}]

                mappedToArray2 = block2.map(d => Array.from(Object.values(d))); /* 將資料存進陣列之中 */
                
                var anomaly = data.getValue(selection.row, 4); /* 顯示是何種異常 */

                /* 匯出變數 */
                localStorage.setItem("A", mappedToArray1); 
                localStorage.setItem("B", mappedToArray2);
                localStorage.setItem("anomaly", anomaly);
            }
            
        }
       

        



        google.visualization.events.addListener(chart, 'select', function() {
            /* 發生點擊事件之後建立浮動視窗 */
            var sel = chart.getSelection();
            const jsFrame = new JSFrame();

            /* 產生浮動視窗 */
            const frame = jsFrame.create({
                    title: 'Window', /* 標題 */
                    appearanceName : 'redstone', /* 視窗類型 */
                    style: {
                        overflow:'auto',
                        width: '100%',
                    },
                    left: 500, top: 20, width: 720, height: 720, /* 第一時間出現的位置 */
                    movable: true,//Enable to be moved by mouse,
                    resizable: true,//Enable to be resized by mouse
                    url: 'gui3.html', /* 連結的目標 */
                }
            );
            
            if (sel) { /* 點擊進行選取之後 */

                frame.show();//Show the window
                //var value = data.getValue(selection.row, 0);
               // alert('The user selected ' + (selection.row == null ? 'something' : data.getValue(selection.row, 0)) );
            }
        });
       
    });


}

