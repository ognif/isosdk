namespace CSharpImageEditSample
{
    partial class KPropertiesDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(KPropertiesDialog));
            this.buttonClose = new System.Windows.Forms.Button();
            this.tabControl = new System.Windows.Forms.TabControl();
            this.generalTabPage = new System.Windows.Forms.TabPage();
            this.listViewParams = new System.Windows.Forms.ListView();
            this.columnHeaderParam = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeaderVal = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.allocationTabPage = new System.Windows.Forms.TabPage();
            this.allocationListView = new System.Windows.Forms.ListView();
            this.extentLocationColumn = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.extentLengthColumn = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.tabControl.SuspendLayout();
            this.generalTabPage.SuspendLayout();
            this.allocationTabPage.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonClose
            // 
            this.buttonClose.Location = new System.Drawing.Point(252, 367);
            this.buttonClose.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(100, 28);
            this.buttonClose.TabIndex = 0;
            this.buttonClose.Text = "Close";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.generalTabPage);
            this.tabControl.Controls.Add(this.allocationTabPage);
            this.tabControl.Location = new System.Drawing.Point(16, 15);
            this.tabControl.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(336, 345);
            this.tabControl.TabIndex = 2;
            // 
            // generalTabPage
            // 
            this.generalTabPage.Controls.Add(this.listViewParams);
            this.generalTabPage.Location = new System.Drawing.Point(4, 25);
            this.generalTabPage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.generalTabPage.Name = "generalTabPage";
            this.generalTabPage.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.generalTabPage.Size = new System.Drawing.Size(328, 316);
            this.generalTabPage.TabIndex = 0;
            this.generalTabPage.Text = "General";
            this.generalTabPage.UseVisualStyleBackColor = true;
            // 
            // listViewParams
            // 
            this.listViewParams.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderParam,
            this.columnHeaderVal});
            this.listViewParams.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listViewParams.Location = new System.Drawing.Point(4, 4);
            this.listViewParams.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.listViewParams.Name = "listViewParams";
            this.listViewParams.Size = new System.Drawing.Size(320, 308);
            this.listViewParams.TabIndex = 2;
            this.listViewParams.UseCompatibleStateImageBehavior = false;
            this.listViewParams.View = System.Windows.Forms.View.Details;
            // 
            // columnHeaderParam
            // 
            this.columnHeaderParam.Text = "Parameter";
            this.columnHeaderParam.Width = 105;
            // 
            // columnHeaderVal
            // 
            this.columnHeaderVal.Text = "Value";
            this.columnHeaderVal.Width = 139;
            // 
            // allocationTabPage
            // 
            this.allocationTabPage.Controls.Add(this.allocationListView);
            this.allocationTabPage.Location = new System.Drawing.Point(4, 25);
            this.allocationTabPage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.allocationTabPage.Name = "allocationTabPage";
            this.allocationTabPage.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.allocationTabPage.Size = new System.Drawing.Size(328, 316);
            this.allocationTabPage.TabIndex = 1;
            this.allocationTabPage.Text = "Allocation";
            this.allocationTabPage.UseVisualStyleBackColor = true;
            // 
            // allocationListView
            // 
            this.allocationListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.extentLocationColumn,
            this.extentLengthColumn});
            this.allocationListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.allocationListView.Location = new System.Drawing.Point(4, 4);
            this.allocationListView.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.allocationListView.Name = "allocationListView";
            this.allocationListView.Size = new System.Drawing.Size(320, 308);
            this.allocationListView.TabIndex = 0;
            this.allocationListView.UseCompatibleStateImageBehavior = false;
            this.allocationListView.View = System.Windows.Forms.View.Details;
            // 
            // extentLocationColumn
            // 
            this.extentLocationColumn.Text = "Extent Location";
            this.extentLocationColumn.Width = 100;
            // 
            // extentLengthColumn
            // 
            this.extentLengthColumn.Text = "Extent Length (bytes)";
            this.extentLengthColumn.Width = 150;
            // 
            // KPropertiesDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(355, 394);
            this.Controls.Add(this.tabControl);
            this.Controls.Add(this.buttonClose);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(373, 441);
            this.Name = "KPropertiesDialog";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Properties";
            this.tabControl.ResumeLayout(false);
            this.generalTabPage.ResumeLayout(false);
            this.allocationTabPage.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage generalTabPage;
        private System.Windows.Forms.TabPage allocationTabPage;
        private System.Windows.Forms.ListView listViewParams;
        private System.Windows.Forms.ColumnHeader columnHeaderParam;
        private System.Windows.Forms.ColumnHeader columnHeaderVal;
        private System.Windows.Forms.ListView allocationListView;
        private System.Windows.Forms.ColumnHeader extentLocationColumn;
        private System.Windows.Forms.ColumnHeader extentLengthColumn;
    }
}