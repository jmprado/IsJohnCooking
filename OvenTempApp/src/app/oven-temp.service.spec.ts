import { TestBed } from '@angular/core/testing';

import { OvenTempService } from './oven-temp.service';

describe('OvenTempService', () => {
  let service: OvenTempService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(OvenTempService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
