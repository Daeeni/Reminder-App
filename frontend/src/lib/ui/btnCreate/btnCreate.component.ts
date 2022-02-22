import { Component, EventEmitter, Input, Output } from '@angular/core';

@Component({
  selector: 'create',
  templateUrl: './btnCreate.component.html',
  styleUrls: ['./btnCreate.component.scss'],
})
export class BtnCreateComponent {
  @Input() backgroundColor: string = '#d6d6d6';
  @Input() borderRadius: string = '10px';
  @Input() height = '50px';
  @Input() opacity = 0.5;
  @Input() margin = '0% 0%';
  @Output() onCreateButton = new EventEmitter<void>();

  clickEvent(): void {
    this.onCreateButton.emit();
  }
}
